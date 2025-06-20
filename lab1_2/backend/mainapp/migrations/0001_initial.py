# Generated by Django 5.2 on 2025-04-12 12:19

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Employee',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('hire_date', models.DateField()),
                ('termination_date', models.DateField(blank=True, null=True)),
                ('position', models.CharField(max_length=50)),
                ('department', models.CharField(max_length=50)),
                ('employee_id', models.CharField(max_length=10, unique=True)),
                ('is_on_leave', models.BooleanField(default=False)),
            ],
        ),
    ]
