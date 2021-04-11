from django.contrib import admin
from .models import Set,Question,Answer,AnswerClient

admin.site.register(Set)
admin.site.register(Question)
admin.site.register(Answer)
admin.site.register(AnswerClient)