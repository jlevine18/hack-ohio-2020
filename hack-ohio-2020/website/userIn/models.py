from django.db import models

# Create your models here.

class Weights(models.Model):
    environment = models.IntegerField(blank = False)
    time = models.IntegerField(blank = False)
    trucks = models.IntegerField(blank = False)
    distance = models.IntegerField(blank = False)

class Waypoint(models.Model):
    street = models.CharField(max_length = 120, blank = False)
    building_num = models.CharField(max_length = 8, blank = False)
    state = models.CharField(max_length = 120, blank = False)
    zipcode = models.CharField(max_length = 10, blank = False)
    is_warehouse = models.BooleanField()