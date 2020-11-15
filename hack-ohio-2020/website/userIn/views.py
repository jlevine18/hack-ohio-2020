from django.shortcuts import render
from django.template import loader

from .models import Weights

# Create your views here.

def index(request):
    template = loader.get_template('userIn/index.html')
    if(len(request.POST)==1):
        context = {'e':"50",
                   'ti':"50",
                   'tr':"50",
                   'c':"50",}

    context = {'e':request.POST.get('enviro'),
               'ti':request.POST.get('time'),
               'tr':request.POST.get('truck'),
               'c':request.POST.get('cost'),}
    print(context)

    return render(request, 'userIn/index.html', context)
