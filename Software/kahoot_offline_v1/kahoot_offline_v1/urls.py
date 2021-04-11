"""kahoot_offline_v1 URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.11/topics/http/urls/
"""
# Django imports
from django.conf.urls import include, url
from django.contrib import admin
from django.contrib.auth import views as auth_views
# from django.views.generic import TemplateView
from django.urls import include, path

from . import views
urlpatterns = [
    # Examples:

    path('',views.index),
    path('create-set-questions/',views.create_set_questions),
    path('admin/', admin.site.urls),

]
