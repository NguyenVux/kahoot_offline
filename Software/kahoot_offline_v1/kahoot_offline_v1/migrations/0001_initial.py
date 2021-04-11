# Generated by Django 3.1.7 on 2021-03-14 10:02

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Set',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=255)),
                ('description', models.TextField()),
                ('timeout_each_question', models.IntegerField()),
                ('type_of_set', models.CharField(max_length=255)),
            ],
        ),
        migrations.CreateModel(
            name='Question',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=255)),
                ('image_url', models.CharField(max_length=255)),
                ('question_description', models.TextField()),
                ('is_correct', models.BooleanField(default=False)),
                ('belong_to_set', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='kahoot_offline_v1.set')),
            ],
        ),
        migrations.CreateModel(
            name='AnswerClient',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('client_id', models.IntegerField()),
                ('time_ans', models.IntegerField()),
                ('is_true', models.BooleanField(default=False)),
                ('cans_for_quest', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='kahoot_offline_v1.question')),
            ],
        ),
        migrations.CreateModel(
            name='Answer',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('ans_description', models.TextField()),
                ('is_correct', models.BooleanField(default=False)),
                ('ans_for_ques', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='kahoot_offline_v1.question')),
            ],
        ),
    ]