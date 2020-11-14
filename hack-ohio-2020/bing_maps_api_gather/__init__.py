
__version__ = "0.1"
__author__ = "Jacob Levine <jlevine4@illinois.edu"
__all__ = ["config_avoid_types", "config_material_restrictions", "get_directions"]

import requests
import datetime


def config_avoid_types(
    avoid_highways: bool = False,
    avoid_tollways: bool = False,
    avoid_ferrys: bool = False,
    minimize_highways: bool = False,
    minimize_tollways: bool = False,
    avoid_border_crossings: bool = False,
    minimize_left_turns: bool = False,
    minimize_right_turns: bool = False,
    minimize_u_turns: bool = False,
) -> list:
    restrictions = []
    if avoid_highways:
        restrictions.append("highways")
    if avoid_tollways:
        restrictions.append("tolls")
    if avoid_ferrys:
        restrictions.append("ferry")
    if minimize_highways:
        restrictions.append("minimizeHighways")
    if minimize_tollways:
        restrictions.append("minimizeTolls")
    if avoid_border_crossings:
        restrictions.append("borderCrossing")
    if minimize_left_turns:
        restrictions.append("minimizeAgainstDrivingSideTurn")
    if minimize_right_turns:
        restrictions.append("minimizeDrivingSideTurn")
    if minimize_u_turns:
        restrictions.append("minimizeUTurn")
    return restrictions


def config_material_restrictions(
    combustable: bool = False,
    corrosive: bool = False,
    explosive: bool = False,
    flammable: bool = False,
    flammable_solid: bool = False,
    gas: bool = False,
    water_hazard: bool = False,
    organic: bool = False,
    poisonous: bool = False,
    poisionous_inhalation: bool = False,
    radioactive: bool = False,
):
    restrictions = []
    if combustable:
        restrictions.append("C")
    if corrosive:
        restrictions.append("Cr")
    if explosive:
        restrictions.append("E")
    if flammable:
        restrictions.append("F")
    if flammable_solid:
        restrictions.append("Fs")
    if gas:
        restrictions.append("G")
    if water_hazard:
        restrictions.append("WH")
    if organic:
        restrictions.append("O")
    if poisonous:
        restrictions.append("P")
    if poisionous_inhalation:
        restrictions.append("PI")
    if radioactive:
        restrictions.append("R")
    return restrictions


def get_directions(
    addresses: list,
    consider_traffic: bool,
    avoid_types: list,
    vehicle_hazardous_materials: list,
    departure_time: datetime.datetime,
    key: str,
) -> dict:
    request_string = "https://dev.virtualearth.net/REST/v1/Routes/Truck?"
    count = 0
    for address in addresses:
        if address == addresses[0] or address == addresses[-1]:
            request_string += "wp." + str(count) + "=" + address + "&"
        else:
            request_string += "vwp." + str(count) + "=" + address + "&"
        count += 1

    if consider_traffic:
        request_string += "optimize=timeWithTraffic&"

    if len(avoid_types) != 0:
        request_string += "avoid="
        for avoid_type in avoid_types:
            request_string += avoid_type + ","
        # cut off the last comma
        request_string = request_string[:-1]
        request_string += "&"

    if len(vehicle_hazardous_materials) != 0:
        request_string += "vehicleHazardousMaterials="
        for material in vehicle_hazardous_materials:
            request_string += material + ","
        # cut off the last comma
        request_string = request_string[:-1]
        request_string += "&"
    else:
        request_string += "vehicleHazardousMaterials=None&"
    if departure_time != None:
        request_string += departure_time.strftime("%m/%d/%Y %H:%M:%S") + "&"

    request_string += "key=" + key
    r = requests.get(request_string)
    return r.json()
