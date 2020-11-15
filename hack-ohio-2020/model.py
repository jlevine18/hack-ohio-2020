import heapq
from bing_maps_gather import *
import datetime
import copy

api_key = #add here


class TruckConfig:
    def __init__(
        self,
        consider_traffic: bool,
        avoid_types: list,
        material_restrictions: list,
        truck_capacity: float,
    ):
        self.consider_traffic = consider_traffic
        self.avoid_types = avoid_types
        self.material_restrictions = material_restrictions
        self.truck_capacity = truck_capacity


class TruckRoute:
    def __init__(self, vertex_list: list = []):
        self.queue = []
        self.vertex_queue = vertex_list


class RoutingConnection:
    def __init__(
        self, other_index: int, distance: float, time: float, trucks_using: list = []
    ):
        self.other_index = other_index
        self.distance = distance
        self.time = time
        self.time_penalty = 0
        self.trucks_using = trucks_using
        self.trucks_left = trucks_using


class RoutingVertex:
    def __init__(self, address: str, source_amount: float = 0, sink_amount: float = 0):
        self.address = address
        self.connections = []
        self.source_amount = source_amount
        self.sink_amount = sink_amount
        self.target_outflow = 0
        self.target_inflow = 0

    def add_truck_route_to_list(
        self, truck_index: int, other_index: int, distance: float, time: float
    ):
        for connection in self.connections:
            if connection.other_index == other_index:
                connection.trucks_using.append(truck_index)
                return
        self.connections.append(
            RoutingConnection(other_index, distance, time, [truck_index])
        )

    def copy_constant(self):
        return RoutingVertex(self.address, self.source_amount, self.sink_amount)


class RoutingGraphDirected:
    def __init__(
        self, truck_config: TruckConfig, vertex_list: list = [], truck_list: list = []
    ):
        self.vertex_list = vertex_list
        self.truck_list = truck_list
        self.truck_config = truck_config
        self.distance_matrix = []
        self.time_matrix = []
        for from_ in vertex_list:
            line_dist = []
            line_time = []
            for to_ in vertex_list:
                directions = get_directions(
                    [from_.address, to_.address],
                    self.truck_config.consider_traffic,
                    self.truck_config.avoid_types,
                    self.truck_config.material_restrictions,
                    apikey,
                )
                line_dist.append(
                    directions["resourceSets"][0]["resources"][0]["travelDistance"]
                )
                line_time.append(
                    ["resourceSets"][0]["resources"][0]["travelDurationTraffic"]
                )
            distance_matrix.append(line_dist)
            time_matrix.append(line_time)

    def add_vertex(self, new_vertex: RoutingVertex):
        self.vertex_list.append(new_vertex)
        new_line_dist = []
        new_line_tie = []

        for other in range(len(vertex_list)):
            directions_out = get_directions(
                [new_vertex.address, vertex_list[other].address],
                self.truck_config.consider_traffic,
                self.truck_config.avoid_types,
                self.truck_config.material_restrictions,
                apikey,
            )
            directions_inm = get_directions(
                [vertex_list[other].address, new_vertex.address],
                self.truck_config.consider_traffic,
                self.truck_config.avoid_types,
                self.truck_config.material_restrictions,
                apikey,
            )
            distance_matrix[other].append(
                directions_out["resourceSets"][0]["resources"][0]["travelDistance"]
            )
            time_matrix[other].append(
                directions_out["resourceSets"][0]["resources"][0][
                    "travelDurationTraffic"
                ]
            )
            new_line_dist.append(
                directions_in["resourceSets"][0]["resources"][0]["travelDistance"]
            )
            new_line_time.append(
                directions_in["resourceSets"][0]["resources"][0][
                    "travelDurationTraffic"
                ]
            )

        distance_matrix.append(new_line_dist)
        time_matrix.append(new_line_time)
        return len(self.vertex_list - 1)

    def add_truck(self, new_truck: TruckRoute):
        self.truck_list.append(new_truck)
        retval = len(self.truck_list) - 1
        for i in range(len(new_truck.queue) - 1):
            vertex_list[i].add_truck_route_to_list(
                retval, i + 1, distance_matrix[i][i + 1], time_matrix[i][i + 1]
            )
        vertex_list[-1].add_truck_route_to_list(
            retval, 0, distance_matrix[-1][0], time_matrix[-1][0]
        )
        return retval

    def copy_constant(self):
        new_rgd = RoutingGraphDirected(self.truck_config)
        for vertex in self.vertex_list:
            new_rgd.vertex_list.append(vertex.copy_constant)
        new_rgd.distance_matrix = self.distance_matrix
        new_rgd.time_matrix = self.time_matrix

    def prepare_moves(self):
        source_queue = []
        for vertex in range(len(self.vertex_list)):
            if self.vertex_list[vertex].source_amount > 0:
                source_queue.append(vertex)
        while len(source_queue) > 0:
            new_source = source_queue.pop(0)
            vertex_queue = []
            heapq.heappush(vertex_queue, (0, new_source, []))
            visited_pts = []
            while len(vertex_queue) > 0:
                dist, index, pathing = heapq.heappop(vertex_queue)
                if index in visited_pts:
                    continue
                visited_pts.append(index)
                if (
                    self.vertex_list[index].sink_amount
                    - self.vertex_list[vertex].target_inflow
                    > 0
                ):
                    flow = max(
                        self.vertex_list[index].sink_amount
                        - self.vertex_list[vertex].target_inflow,
                        self.vertex_list[new_source].source_amount
                        - self.vertex_list[new_source].target_outflow,
                        self.truck_config.truck_capacity,
                    )
                    self.vertex_list[index].target_inflow += flow
                    vertex_last = index
                    for vertex, truck in pathing:
                        self.vertex_list[vertex].target_inflow += flow
                        self.vertex_list[vertex].target_outflow += flow
                        self.truck_list[truck].queue.append(vertex)
                        # dw about repeats, dist(a,a) = 0.
                        self.truck_list[truck].queue.append(vertex_last)
                    self.vertex_list[new_source].target_inflow -= flow
                    if (
                        self.vertex_list[new_source].source_amount
                        - self.vertex_list[new_source].target_outflow
                        > 0
                    ):
                        source_queue.append(new_source)
                    break
                for connection in self.vertex_list[index].connections:
                    pathing_total = copy.deepcopy(pathing)
                    truck_used = connection.trucks_left.pop()
                    pathing_total.insert(0, (index, truck_used))
                    if len(connection.trucks_left) == 0:
                        connection.trucks_left = connection.trucks_using
                        connection.time_penalty += self.time_matrix[index][
                            connection.other_index
                        ]
                    heapq.heappush(
                        vertex_queue,
                        (
                            dist + connection.time + connection.time_penalty,
                            connection.other_index,
                            pathing_total,
                        ),
                    )

    def get_loss(
        self, time_weight, environmental_weight, distance_weight, cargo_weight
    ):
        total_driving_time = 0
        total_distance = 0
        max_time = 0
        cargo_issues = 0
        for truck in self.truck_list:
            current_location = truck.queue[0]
            time = 0
            distance = 0
            for location in truck.queue:
                distance += self.distance_matrix[current_location][location]
                time += self.time_matrix[current_location][location]
            if time > max_time:
                max_time = time
            total_driving_time += time
            total_distance += distance
        for vertex in self.vertex_list:
            cargo_issues += vertex.sink_amount - vertex.target_inflow
        return (
            time_weight * max_time
            + distance_weight * total_distance
            + environmental_weight * total_driving_time
            + cargo_weight * cargo_issues
        )
