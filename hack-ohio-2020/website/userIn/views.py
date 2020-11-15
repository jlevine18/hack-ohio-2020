from django.shortcuts import render
from django.template import loader

# Create your views here.

def index(request):
    template = loader.get_template('userIn/index.html')
    context = {'e':request.POST.get('environment'),
               't':request.POST.get('time'),
               'd':request.POST.get('distance'),
               'c':request.POST.get('cost'),}
    print(request.POST.get('environment'))
    return render(request, 'userIn/index.html', context)
