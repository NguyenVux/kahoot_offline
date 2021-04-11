from django.db import models


class Set(models.Model):
    name = models.CharField(max_length=255)
    description = models.TextField()
    timeout_each_question = models.IntegerField()
    type_of_set = models.CharField(max_length=255)


class Question(models.Model):
    title = models.CharField(max_length=255)
    image_url = models.CharField(max_length=255)
    question_description = models.TextField()
    is_correct = models.BooleanField(default=False)
    belong_to_set = models.ForeignKey(Set, on_delete=models.CASCADE)


class Answer(models.Model):
    ans_description = models.TextField()
    is_correct = models.BooleanField(default=False)
    ans_for_ques = models.ForeignKey(Question, on_delete=models.CASCADE)


class AnswerClient(models.Model):
    client_id = models.IntegerField()
    time_ans = models.IntegerField()
    is_true = models.BooleanField(default=False)
    cans_for_quest = models.ForeignKey(Question, on_delete=models.CASCADE)
