from django.contrib import admin
from django.urls import path, include

from django.conf import settings
from django.conf.urls.static import static


from rest_framework import routers


from mainapp.views import EmployeeViewSet


urlpatterns = [
    path('admin/', admin.site.urls),
    path('employee.get', EmployeeViewSet.as_view({'get': 'list'})),  
    path('employee.get/<pk>', EmployeeViewSet.as_view({'get': 'retrieve'})),    
    path('employee.create', EmployeeViewSet.as_view({'post': 'create'})),  
    path('employee.update/<pk>', EmployeeViewSet.as_view({'post': 'update'})), 
    path('employee.delete/<pk>', EmployeeViewSet.as_view({'get': 'destroy'})),
]
urlpatterns += static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)