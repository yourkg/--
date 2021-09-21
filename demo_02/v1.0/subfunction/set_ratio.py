import os
import random

def writer_objfile(flag,class_num,class_names_path,train_path,weight_save,obj_data_path,val_path=""):
    if not os.path.exists(weight_save):
        os.makedirs(weight_save)  
    if os.path.exists(obj_data_path):#判断此文件是否存在 ，存在删除
        os.remove(obj_data_path) 
    if flag == "0":
        
        with open(obj_data_path, "a+") as f:
            f.write("classes= "+str(class_num)+"\n")
            f.write("train  = "+train_path+"\n")
            f.write("names = "+class_names_path+"\n")
            f.write("backup ="+weight_save+"\n")
    else:
        with open(obj_data_path, "a+") as f:
            f.write("classes= "+str(class_num)+"\n")
            f.write("train  = "+train_path+"\n")
            f.write("val  = "+val_path+"\n")
            f.write("names = "+class_names_path+"\n")
            f.write("backup ="+weight_save+"\n")



def rw_floder(flag,per,train_path,val_path="",tr_ratio = None,va_ratio = None):
    suffix = [".png",".jpg"]
    image_total_image =[]
     
    for per_image in os.listdir(per):
        if (os.path.splitext(per_image)[-1]) in suffix:
            image_path = os.path.join(per, per_image)
            image_total_image.append(image_path)
    # print(image_total_image)
    if flag == "0":
        for image_one in image_total_image:  
                        
            with open(train_path, "a+") as f:
                f.write(image_one+"\n")
    
    else:
        num = len(image_total_image)       
        va_num = int(num * va_ratio)
        print(va_num)
        val_image = random.sample(image_total_image, va_num)
        train_image = list(set(image_total_image) - set(val_image))
        print(len(train_image))       
        # train_image = random.sample(image_total_image, tr_num)
        
        for train_img in train_image:
            with open(train_path, "a+") as f:
                f.write(train_img+"\n")

        for val_img in val_image:
            with open(val_path, "a+") as f:
                f.write(val_img+"\n")

def training_set(ratio,train_folder,train_path,val_path=""):
    if os.path.exists(train_path):#判断此文件是否存在 ，存在删除
        os.remove(train_path)
    if os.path.exists(val_path):#判断此文件是否存在 ，存在删除
        os.remove(val_path)  
    for per_folder in train_folder:
        if os.path.exists(per_folder):
            if ratio == "0": #全为训练集
                rw_floder(ratio,per_folder,train_path)
            else:
                getval_path = val_path
                train_percent,val_percent=ratio.split(":")
                train_ratio = int(train_percent)/10
                val_ratio = int(val_percent)/10
                rw_floder(ratio,per_folder,train_path,val_path=getval_path,tr_ratio = train_ratio,va_ratio = val_ratio)



# ratio ="8:2"

# train_floder = [r"D:\pig_pic\pigtest1\1",r"D:\pig_pic\pigtest1\2",r"D:\pig_pic\pigtest1\3"]#数据集文件夹列表
# training_set(ratio,train_floder)
# class_names_path=r"D:\云平台\v0.3\classes.names"

# weight_save=r"D:\云平台\v0.3\subfunction\yolov3_train" 
# train_path = r"D:\云平台\v0.3\subfunction\train.txt"
# val_path = r"D:\云平台\v0.3\subfunction\val.txt"
# #输入参数有训练集和验证集的占比，标注好的训练图片文件夹，类别名称文件，类别数量，权重文件保存文件夹
# writer_objfile(ratio,1,class_names_path,train_path,weight_save,val_path=val_path)
# r"D:\云平台\v0.3\subfunction\yolov3_train" r"D:\云平台\v0.3\classes.names"