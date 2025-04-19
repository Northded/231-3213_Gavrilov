from django.shortcuts import render

from django.shortcuts import render


from django.conf import settings


import rest_framework
from rest_framework import  viewsets


from .models import Employee
from .serializers import EmployeeSerializer


class EmployeeViewSet(viewsets.ModelViewSet):
    queryset = Employee.objects.all()
    serializer_class = EmployeeSerializer
