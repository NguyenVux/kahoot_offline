from django.http import HttpResponse
from django.shortcuts import render
from .forms import (
    AnswerModelFormSet,
    AnswerModelForm,
    QuestionModelFormSet,
    SetModelForm,
    AnswerFormset
)

from .models import (Set, Question, Answer)


def index(request):
    return render(request, 'core/index.html', {
        'path': request.path
    })


def create_set_questions(request):
    if request.method == 'GET':
        setform = SetModelForm(request.GET or None)
        answer1 = AnswerFormset(request.GET or None)
        # answer2 = AnswerModelForm(request.GET or None)
        # answer3 = AnswerModelForm(request.GET or None)
        # answer4 = AnswerModelForm(request.GET or None)
        questionform = QuestionModelFormSet(queryset=Set.objects.none())
        # answerform = AnswerModelFormSet(queryset=Question.objects.none())
    if request.method == 'POST':
        print('=======================')
        setform = SetModelForm(request.POST)
        questionform = QuestionModelFormSet(request.POST)
        # answerform = AnswerModelFormSet(request.POST)
        answer1 = AnswerModelForm(request.POST)
        # answer2 = AnswerModelForm(request.POST)
        # answer3 = AnswerModelForm(request.POST)
        # answer4 = AnswerModelForm(request.POST)
        print(request.POST)
        print(questionform, 'ques')
        # print(setform)
        # print(an

    context = {
        'set': setform,
        'answer1': answer1,
        # 'answer2': answer2,
        # 'answer3': answer3,
        # 'answer4': answer4,
        'question': questionform
    }
    return render(request, 'questions/create_set.html', context)
