import model
import re

#GetMostAchievedAchievementInfo

def find_len_param(param:model.Object, method:model.Method):
    for i in range(len(method.params)):
        param = method.params[i]
        if param.size_for:
            continue
        if param.is_integer and re.findall(r"(len|size|count|max|cch)", param.name, re.IGNORECASE):
            return i

    return -1

def optimize_buffer(method:model.Method):
    for param in method.params:
        if param.is_pointer and param.is_primitive:
            len_param = find_len_param(param, method)
           
            if len_param != -1:
                param.is_buffer = True
                param.buffer_size = method.params[len_param]
                method.params[len_param].size_for = param

def optimize(db:dict):
    for key in db:
        object = db[key]

        for method in object.methods:
            optimize_buffer(method)

