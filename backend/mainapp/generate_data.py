# mainapp/generate_data.py
import random
import string
import datetime
from django.db import transaction
from django.contrib.auth.models import Group, User
from faker import Faker
from .models import Employee  

def seed_employees():
    fake = Faker()
    positions = ['Менеджер', 'Инженер', 'Аналитик', 'Тестировщик']
    departments = ['IT', 'Финансы', 'Маркетинг', 'HR']

    with transaction.atomic():
        for _ in range(100):
            emp = Employee()
            emp.hire_date = fake.date_between(start_date='-5y', end_date='today')
            
            if random.random() < 0.2:
                emp.termination_date = fake.date_between(
                    start_date=emp.hire_date, 
                    end_date='today'
                )
            
            emp.position = random.choice(positions)
            emp.department = random.choice(departments)
            emp.employee_id = f"EMP-{''.join(random.choices(string.digits, k=6))}"
            emp.is_on_leave = random.random() < 0.15
            emp.save()
        
        print(f"Создано {Employee.objects.count()} сотрудников")