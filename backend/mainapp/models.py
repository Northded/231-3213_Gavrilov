from django.db import models

# Create your models here.
class Employee(models.Model):
    hire_date = models.DateField()
    termination_date = models.DateField(null=True, blank=True)
    position = models.CharField(max_length=50)
    department = models.CharField(max_length=50)
    employee_id = models.CharField(max_length=10, unique=True)
    is_on_leave = models.BooleanField(default=False)
   