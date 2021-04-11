from django import forms
from .models import (Set, Question, Answer)
from django.forms import (formset_factory, modelformset_factory)

classes_input = 'border-b-2 p-2 my-4 focus:outline-none focus:border-b-4 focus:border-purple-600  w-full'
classes_textarea = 'border-b-2 p-2 my-4 resize-none focus:outline-none focus:border-b-4 focus:border-purple-600  w-full'
classes_select = 'border-b-2 p-2 my-4 focus:outline-none focus:border-b-4 focus:border-purple-600  w-full'
classes_radio = "form-radio h-5 w-5 checked:bg-purple-600"


class SetModelForm(forms.ModelForm):
    class Meta:
        model = Set
        fields = ('name', 'type_of_set', 'description', 'timeout_each_question')
        widgets = {
            'name': forms.TextInput(attrs={'class': classes_input, 'placeholder': "Nhập tiêu đề cho bộ câu hỏi"}),
            'type_of_set': forms.TextInput(attrs={'class': classes_input, 'placeholder': "Phân loại cho bộ câu hỏi: Toán, Tiếng Việt, ..."}),
            'description': forms.Textarea(attrs={'class': classes_textarea, 'placeholder': "Nhập mô tả cho bộ câu hỏi", 'rows': "4"}),
            'timeout_each_question': forms.NumberInput(attrs={'class': classes_input, 'placeholder': "Thời gian cho mỗi câu hỏi 15,30,40 giây"})
        }


# class QuestionModelForm(forms.ModelForm):
#     class Meta:
#         model = Question
#         fields = ('title', 'image_url')
#         widget = {
#             'title': forms.TextInput(attrs={'class': classes_input, 'placeholder': "Câu hỏi", 'data-question': '1'}),
#             'image_url': forms.TextInput(attrs={'class': classes_input, 'placeholder': "Hình ảnh", 'data-img-question': '1'})
#         }

class AnswerForm(forms.Form):
    ans_description = forms.CharField(
        label="",
        widget=forms.TextInput(attrs={
            'class': classes_input, 'placeholder': "Câu trả lời", 'data-ans-question': '1'}
        )
    )
    is_correct = forms.ChoiceField(
        label="",
        widget=forms.RadioSelect(
            attrs={'class': classes_radio},
            choices=[('0', ""), ('1', ""), ('2', ""), ('3', "")])
    )


class AnswerModelForm(forms.ModelForm):

    class Meta:
        model = Answer
        fields = ('ans_description', 'is_correct')
        labels = {
            'ans_description': "",
            'is_correct': ""
        }
        widgets = {
            'ans_description': forms.TextInput(attrs={'class': classes_input, 'placeholder': "Câu trả lời", 'data-ans-question': '1'}),
            'is_correct': forms.RadioSelect(attrs={'class': classes_radio}, choices=[('0', ""), ('1', ""), ('2', ""), ('3', "")])
        }


# SetModelFormSet = modelformset_factory(
#     Set,
#     fields=('name', 'type_of_set', 'description', 'timeout_each_question'),
#     widgets={
#         'name': forms.TextInput(attrs={'class': classes_input, 'placeholder': "Nhập tiêu đề cho bộ câu hỏi"}),
#         'type_of_set': forms.TextInput(attrs={'class': classes_input, 'placeholder': "Phân loại cho bộ câu hỏi: Toán, Tiếng Việt, ..."}),
#         'description': forms.Textarea(attrs={'class': classes_textarea, 'placeholder': "Nhập mô tả cho bộ câu hỏi", 'rows': "4"}),
#         'timeout_each_question': forms.NumberInput(attrs={'class': classes_input, 'placeholder': "Thời gian cho mỗi câu hỏi 15,30,40 giây"})
#     }
# )
AnswerFormset = formset_factory(AnswerForm, min_num=3)

AnswerModelFormSet = modelformset_factory(
    Answer,
    fields=('ans_description', 'is_correct'),
    # extra=1,
    widgets={'ans_description': forms.TextInput(attrs={
        'class': classes_input,
        'placeholder': "Câu trả lời",
        'data-ans-question': '1'}),
        'is_correct': forms.RadioSelect(attrs={'class': classes_radio}, choices=[('1', ""), ('2', ""), ('3', ""), ('4', "")])
    })
QuestionModelFormSet = modelformset_factory(
    Question,
    extra=1,
    fields=('title', 'image_url', 'is_correct'),
    widgets={
        'title': forms.TextInput(attrs={'class': classes_input, 'placeholder': "Câu hỏi", 'data-question': '1'}),
        'image_url': forms.TextInput(attrs={'class': classes_input, 'placeholder': "Hình ảnh", 'data-img-question': '1'}),
        'is_correct': forms.RadioSelect(attrs={'class': classes_radio}, choices=[('1', "")])
    }
)
