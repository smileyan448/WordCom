%% manually select centers
function [z1, qq, cen1, z2, qq2, N_inf_t,cen2]=K_rank_D_manual(A,cc,assignment,auto)
% % using diffferent centrality measures(global centrality measures, local centrality measures)
tstart = tic;

ND=size(A,1);%节点数
new_matrix=adj2vec(A);
dis=batch_distance(new_matrix,new_matrix);
dis=dis-diag(diag(dis));

telapsed = toc(tstart);
disp(telapsed);

for i=1:ND %kernel
        N_inf(i)=0.;
end 
        N_inf2=pagerank_alg(A,0.85);%pagerank_new
% Two cases: 1)        
% with few nodes and pagerank value demonstrate litte divergence
flag = 0;
if flag
   for i=1:ND-1 
          for j=i+1:ND
                 N_inf(i)=N_inf(i)+exp(-((dis(i,j)*dis(i,j))/(N_inf2(i))));      
                 N_inf(j)=N_inf(j)+exp(-((dis(i,j)*dis(i,j))/(N_inf2(j))));       
          end
   end
% % when a network is small, the pagerank value usually need to be modified. 
   N_inf=N_inf+N_inf2';
% % otherwise, the pagerank value is strong enough
else
   N_inf=N_inf2';
end

 nneigh=zeros(1,ND);
 delta=zeros(1,ND);
 %maxd=max(max(dis));
 [N_sorted,ordN]=sort(N_inf,'descend');%降序排列，[value,index]
 delta(ordN(1))=-1.;
 nneigh(ordN(1))=0;
for ii=2:ND   
    list=ordN(1:ii-1);    
    distance=dis(ordN(ii),list);
    [value,index]=min(distance);
    delta(ordN(ii))=value;
    nneigh(ordN(ii))=list(index);
end
delta(ordN(1))=max(delta(:)); %author provided
disp('Generated file:DECISION GRAPH')
disp('column 1:Density')
disp('column 2:Delta')

disp('Select a rectangle enclosing cluster centers')
% scrsz = get(0,'ScreenSize');
% figure('Position',[6 72 scrsz(3)/4. scrsz(4)/1.3]);

%subplot(2,1,1)
tt=plot(N_inf(:),delta(:),'o','MarkerSize',5,'MarkerFaceColor','k','MarkerEdgeColor','k');
% tt=plot(N_inf(1:3),delta(1:3),'o','MarkerSize',5,'MarkerFaceColor','k','MarkerEdgeColor','k');
% hold on
% tt=plot(N_inf(4:8),delta(4:8),'o','MarkerSize',5,'MarkerFaceColor','k','MarkerEdgeColor','b');
% tt=plot(N_inf(17:20),delta(17:20),'o','MarkerSize',5,'MarkerFaceColor','k','MarkerEdgeColor','g');
% hold on
% for i=1:length(N_inf)
%     text(N_inf(i),delta(i),num2str(i));
% end
title ('Decision Graph of the Original Network','FontSize',15.0)

%subplot(2,1,1)
if ~auto
    rect = getrect(1); %rect=[x_min,y_min,weight,height]
    rhomin=rect(1);
    deltamin=rect(2);
    NCLUST=0;
    for i=1:ND
      cl(i)=-1;
    end
    icl=[];
    for i=1:ND
      if ( (N_inf(i)>rhomin) && (delta(i)>deltamin))
         NCLUST=NCLUST+1;
         cl(i)=NCLUST; % 对类中心进行类别指派
         icl(NCLUST)=i;% store centers
      end
    end
    fprintf('NUMBER OF CLUSTERS: %i \n', NCLUST);
    fprintf('Centers are:\n' );
    disp(icl);
end


N_inf_t=(N_inf-min(N_inf))/(max(N_inf)-min(N_inf));
delta_t=(delta-min(delta))/(max(delta)-min(delta));
for i=1:ND
  ind(i)=i;
  gamma(i)=N_inf_t(i)*delta_t(i);
end
[~,index]=sort(gamma,'descend');
if ~isempty(cc)
NCLUST2=size(cc,1);% the number of clusters
else
    %NCLUST2=input('input the number of cluster for K-rank-d:');
     NCLUST2 = 219;
end
    
icl2=index(1:NCLUST2);
for i=1:ND
  cl2(i)=-1;
end
cl2=zeros(ND,1)-1;

for i=1:NCLUST2    
     cl2(icl2(i))=i;     % store centers
end


fprintf('Centers2 are:\n' );
disp(icl2);

%disp('5:iterative k-means');
%assignment=input('Performing assignation, which assignment?');
switch assignment
    case 1
      disp('1:science');
      if ~auto
        for i=1:ND% 从密度最大的点开始考虑，对点进行指派
          if (cl(ordN(i))==-1)
              cl(ordN(i))=cl(nneigh(ordN(i)));
          end
        end
        cl=cl';
      end
        
        for i=1:ND% 从密度最大的点开始考虑，对点进行指派
          if (cl2(ordN(i))==-1)
              cl2(ordN(i))=cl2(nneigh(ordN(i)));
          end
        end
        %cl2=cl2';
    case 2 % nearest assignment
        disp('2:nearest assignment');
        if ~auto
            x=dis(:,icl); 
    %        [~,cl]=min(x,[],2); 
            for i=1:ND
              min_value=min(x(i,:));
              id= find(x(i,:)==min_value);
              if length(id)>1
                  [value,index]=min(N_inf(icl(id)));
                  cl(i)=id(index);
              else
                  cl(i)=id;  
              end      
            end
            cl=cl';
        end
        
        x=dis(:,icl2); 
        %   [~,cl]=min(x,[],2); 
        for i=1:ND
          min_value=min(x(i,:));
          id= find(x(i,:)==min_value);
          if length(id)>1
              [value,index]=min(N_inf(icl2(id)));
              cl2(i)=id(index);
          else
              cl2(i)=id;  
          end      
        end
        
        %cl2=cl2';
    case 3 %iterative nearest assignent   
        disp('3:iterative nearest assignment');
        if ~auto
             x=dis(:,icl); 
            [a,cl]=min(x,[],2);
            %redefine the cluster centers
            maxIter=50;
             num=1;
             while(1)
                 num=num+1;
                cen_new=[];
                for i=1:NCLUST
                    index=find(cl==i);
                    X=A(index,index);              
                    N_inf=pagerank_alg(X,0.85);%pagerank_new                           
                    [value,idx]=max(N_inf);
                    cen_new(length(cen_new)+1)=index(idx);
                end 
                if isequal(icl,cen_new)
                     break;
                end
                if num >=maxIter
                    break;
                end
                num=num+1;
                disp('number of iteration:')
                disp(num);
                icl=cen_new;
                disp(icl)
                x=dis(:,icl);
                for i=1:ND
                  min_value=min(x(i,:));
                  id= find(x(i,:)==min_value);
                  if length(id)>1
                      [value,index]=min(N_inf(icl(id)));
                      cl(i)=id(index);
                  else
                     cl(i)=id;  
                  end   
                end
             end
        end
         
         %cl=cl';
         
         x=dis(:,icl2); 
         [a,cl2]=min(x,[],2);
         %redefine the cluster centers
         maxIter=50;
         num=1;
         while(1)
            num=num+1;
            cen_new=[];
            for i=1:NCLUST2
                index=find(cl2==i);
                X=A(index,index);              
                N_inf=pagerank_alg(X,0.85);%pagerank_new                           
                [value,idx]=max(N_inf);
                cen_new(length(cen_new)+1)=index(idx);
            end 
            if isequal(icl2,cen_new)
                 break;
            end
            if num >=maxIter
                break;
            end
            num=num+1;
            disp('number of iteration:')
            disp(num);
            icl2=cen_new;
            disp(icl2)
            x=dis(:,icl2);
            for i=1:ND
              min_value=min(x(i,:));
              id= find(x(i,:)==min_value);
              if length(id)>1
                  [value,index]=min(N_inf(icl2(id)));
                  cl2(i)=id(index);
              else
                  cl2(i)=id;  
              end   
            end
         end
         
    case 4 %k-means
        disp('4:k-means');
        new_matrix=full(new_matrix);
%         center=new_matrix(:,icl)';
%        [cl,~]=kmeans(new_matrix',NCLUST,'start',center,'emptyaction','singleton');
%        center2=new_matrix(:,icl2)';
%        [cl2,~]=kmeans(new_matrix',NCLUST2,'start',center2,'emptyaction','singleton');
        if ~auto
            [U1,x,cen1]=D_kmeans(new_matrix,NCLUST,icl);
           % disp(cen);
           
        end
         [U2,x,cen2]=D_kmeans(new_matrix,NCLUST2,icl2);
         %disp(cen);
%     case 5
%         new_matrix=full(new_matrix);
%         center=new_matrix(:,icl)';
%        [cl,~]=kmeans(new_matrix',NCLUST,'start',center);
%         num=1;
%         maxIter=50;
%         while(1)
%             num=num+1;
%             cen_new=[];
%             for i=1:size(cc,1)
%                 index=find(cl==i);
%                 A_new=A(index,index);
%                 v=pagerank_new(A_new);
%                 [value,v]=sort(v,'descend');
%                 cen_new(length(cen_new)+1)=index(v(1));
%             end
%             if isequal(icl,cen_new)
%                 break;
%             end
%             if num >=maxIter
%                 break;
%             end
%             icl=cen_new;
%             center=new_matrix(:,icl)';
%             [cl,~]=kmeans(new_matrix',k,'start',center,'emptyaction','singleton');
%         end
%         disp('迭代次数：');
%         disp(num);
    end

switch assignment
    case 4
        if ~auto
            q=1:ND;
            q(2,:)=cl;
            %qq=criterion(q');
            qq=criterion(U1);
            z1=U1(:,2);
        end
        
        q=1:length(cl2);
        q(2,:)=cl2;
        %qq2=criterion(q');
        qq2=criterion(U2);%转化为一行表示一个类

%         [modularity,entropy, density] = evaluate(A,[],U1(:,2));
%         fprintf('modul, entropy, density:%f\t%f\t%f\n',modularity,entropy, density);
%         [modularity2,entropy2, density2] = evaluate(A,C,U2(:,2));
%         fprintf('modul2, entropy2, density2::%f\t%f\t%f\n',modularity2,entropy2, density2);
        
        z2=U2(:,2);
    otherwise
        
        if ~auto
        q=1:ND;
        q(2,:)=cl;
        qq=criterion(q');
        %qq=criterion(U1);
        z1=cl;
        end

%         [modularity,entropy, density] = evaluate(A,C,q(2,:)');
%         fprintf('modul, entropy, density:%f\t%f\t%f\n',modularity,entropy, density);
        q=1:length(cl2);
        q(2,:)=cl2;
        qq2=criterion(q');
        %qq2=criterion(U2);%转化为一行表示一个类
        

%         [modularity2,entropy2, density2] = evaluate(A,C,q(2,:)');
%         fprintf('modul2, entropy2, density2::%f\t%f\t%f\n',modularity2,entropy2, density2);

        z2=cl2;
        
end


% 
% result=[];
% if ~isempty(cc) %with groundtruth
%     disp('results with groundtruth')
%         realz=[];
%         k=size(cc,1);
%         for m=1:k
%             id=find(cc(m,:)>0);
%             realz(size(realz,1)+1:size(realz,1)+length(id),1)=cc(m,id); 
%             realz(size(realz,1)-length(id)+1:size(realz,1),2)=m;
%         end
%         realz2=sortrows(realz,1);
%         realz=realz2(:,2);      
%         
% 
%     if ~auto
%      %  [modularity,entropy, density] = evaluate(A,C,z1); 
%      %   result(size(result,1)+1,:)=[assignment,accuracy(qq,cc),NMI(qq,cc),evalClustering(z1,realz),modularity, density,entropy];
%         result(size(result,1)+1,:)=[assignment,accuracy(qq,cc),NMI(qq,cc),evalClustering(z1,realz)];
%     end
%     %[modularity,entropy, density] = evaluate(A,C,z2); 
%     %result(size(result,1)+1,:)=[assignment,accuracy(qq2,cc),NMI(qq2,cc),evalClustering(z2,realz),modularity, density,entropy];% 根据gamma r
%     result(size(result,1)+1,:)=[assignment,accuracy(qq2,cc),NMI(qq2,cc),evalClustering(z2,realz)];
%     if ~auto
%         %result=[result(1,:),result(2,:)];
%     end
%    
%         
% %without groundtruth (modularity,entropy,density)
% else
%     disp('results without groundtruth')
%     if ~auto
%     
%     [modularity,entropy, density] = evaluate(A,C,z1); 
%     result(size(result,1)+1,:)= [assignment,modularity, density,entropy];
%     [modularity,entropy, density] = evaluate(A,C,z2); 
%     result(size(result,1)+1,:)= [assignment,modularity, density,entropy];
%     %result=[result(1,:),result(2,:)];
%     else
%         
%    [modularity,entropy, density] = evaluate(A,C,z2);
%     result(size(result,1)+1,:)= [assignment,modularity, density,entropy];
%         
%     %result=[result(1,:),result(2,:)];
%     end
% end
% end

