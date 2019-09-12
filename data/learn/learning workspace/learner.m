clc;
clear all;
close all;
%%
disp('Initialization.');
if ismac
    % Code to run on Mac platform
    divider='/';
elseif isunix
    % Code to run on Linux platform
    divider='/';
elseif ispc
    % Code to run on Windows platform
    divider='\';
else
    disp('Platform not supported');
    return;
end
learning_workspase=[pwd,divider];
out_folder=[learning_workspase,'..',divider];
%%
disp('Reading settings from file.');

fileID = fopen('settings.txt','r');
tmp = fscanf(fileID,'%d');
size_of_image = tmp(1);
number_of_neurons = tmp(2);
fclose(fileID);
%%
disp('Finding classifiers.');

list = dir('.');
classifiers={list.name};
folder_flag=[list.isdir];
classifiers(~folder_flag)=[];
classifiers(1:2)=[];

%%
disp('Writing classifiers list.');

nuber_of_classifiers=length(classifiers);
fileID = fopen([out_folder,'classifiers.txt'],'w');
fprintf(fileID,'%d %d\r\n',nuber_of_classifiers,1); %строка с размерами нужна для С++
for i=1:nuber_of_classifiers
    fprintf(fileID,'%s\r\n',classifiers{i});
end
fclose(fileID);
%%
disp('Processing images.');

% size_of_image=30;   %TODO: чтение размера из файла настроек
IMG=cell(nuber_of_classifiers,1);
total_number_of_images=0;
for i=1:nuber_of_classifiers
    cd([learning_workspase,char(classifiers(1,i))])


    list = dir('.');
    img_list={list.name};
    img_list(1:2)=[];
    
    N=length(img_list);
    total_number_of_images=total_number_of_images+N;
    PROCESSED_IMG=cell(N,1);
    
    for j=1:N
        tmp=imread(img_list{j});    
        if size(tmp,3)==3 %Если РГБ преобразование в чб
            tmp=rgb2gray(tmp);
        end
        tmp=imresize(tmp, [size_of_image size_of_image], 'nearest');  %TODO: сравнить результаты с разными методами:
                                                    %'bilinear' 'nearest' 'bicubic'
        PROCESSED_IMG{j}=tmp;
    end
    IMG{i}=PROCESSED_IMG;
end
%%
disp('Creating learning data.');

TargetData=zeros(nuber_of_classifiers,total_number_of_images);
image_iterator=1;
for i=1:nuber_of_classifiers
    for j=1:length(IMG{i})
        tmp=zeros(nuber_of_classifiers,1);
        tmp(i)=1;
        TargetData(:,image_iterator)=tmp;
        image_iterator=image_iterator+1;
    end
end

InputData=zeros(size_of_image*size_of_image,total_number_of_images);
image_iterator=1;
tmp=zeros(size_of_image*size_of_image,1);
for i=1:nuber_of_classifiers
    for j=1:length(IMG{i})
        mat=IMG{i}{j};
        for p=1:size_of_image
            tmp((p-1)*size_of_image+1:p*size_of_image)=(mat(p,:))';
        end
        InputData(:,image_iterator)=tmp;
        image_iterator=image_iterator+1;
    end
end
%%
disp('Teaching neural network.');

% number_of_neurons=30;   %TODO: загрузка из файла
net = feedforwardnet(number_of_neurons);
net = configure(net,InputData,TargetData);
net = train(net,InputData,TargetData,'useParallel','yes','useGPU','yes');
%%
disp('Get network data.');

ranges=net.inputs.range;
IW=net.IW;
b1=net.b{1};
LW=net.LW;
b2=net.b{2};

%post process data
ranges=ranges{1};
IW=IW{1};
LW=LW{2,1};
%%
disp('Saving network data.');

save([out_folder,'net.mat'],'net')
Save_matrix(IW,[out_folder,'weights1.txt']);
Save_matrix(LW,[out_folder,'weights2.txt']);
Save_matrix(ranges,[out_folder,'ranges.txt']);
Save_matrix(b1,[out_folder,'bias1.txt']);
Save_matrix(b2,[out_folder,'bias2.txt']);

%%
function Save_matrix(data,out_file_path)
fileID = fopen(out_file_path,'w');
fprintf(fileID,'%d %d\r\n',size(data));
for i=1:size(data,1)
    for j=1:size(data,2)
        fprintf(fileID,'%16.16f ',data(i,j));
    end
    fprintf(fileID,'\r\n');
end
fclose(fileID);
end