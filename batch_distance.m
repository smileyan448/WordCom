% 通过递归对欧式距离矩阵进行计算
%A is m*N matrix, B is m*M matrix
%distance is  N*M matrix
function distance=batch_distance(A,B)
    num=2;%分成的份数
    n=size(A,2);
    if n>1000
    iter=fix(n/2);    
    tempA=cell(num,1);
    if mode(n,2)==0 % 奇数
    for i=1:num   
        tempA{i}=A(:,(i-1)*iter+1:i*iter);
     %eval(['tempA' num2str(i) '= A(:,(i-1)*iter+1:i*iter)']);
    end
    tempB=cell(num,1);
    for i=1:num   
        tempB{i}=B(:,(i-1)*iter+1:i*iter);
     %eval(['tempB' num2str(i) '= B(:,(i-1)*iter+1:i*iter)']);
    end
    else
        tempA{1}=A(:,1:iter);
        tempA{2}=A(:,iter+1:n);
        tempB{1}=B(:,1:iter);
        tempB{2}=B(:,iter+1:n);        
    end
% recursive algorithm
%     dist1=batch_distance(full(tempA{1}),full(tempB{1}));
%     dist2=batch_distance(full(tempA{1}),full(tempB{2}));
%     dist4=batch_distance(full(tempA{2}),full(tempB{2}));
    dist1=sqdistance(full(tempA{1}),full(tempB{1}));
    dist2=sqdistance(full(tempA{1}),full(tempB{2}));
    dist4=sqdistance(full(tempA{2}),full(tempB{2}));
    d1=[dist1,dist2];
    d2=[dist2',dist4];
    distance=[d1;d2];   
    else
        
%     dist1=sqdistance(full(tempA{1}),full(tempB{1}));
%     dist2=sqdistance(full(tempA{1}),full(tempB{2}));
%     dist4=sqdistance(full(tempA{2}),full(tempB{2}));
%     distance=[dist1,dist2;dist2',dist4];  
      distance=sqdistance(A,B); 
    end
   
   
end