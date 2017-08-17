% my accuracy for speed
% a fast version for computing accuracy: the ratio of correct partitioned nodes.

function[accuracy]=accuracy(result,criterion)

[hang1,lie1]=size(result);
[hang2,lie2]=size(criterion);
total = nnz(result);
[~, loc] = ismember(result, criterion);

[I, ~] = ind2sub([hang2, lie2], loc);
I(result == 0) = 0; % delete the zero-elements
new = I;
disp('step1');

clearvars I J loc lia result criterion;

new2 = zeros(hang2, hang1);
for i=1:hang1
    count = tabulate(new(i, :));
    count(count(:, 1) == 0, :) = [];
    new2(count(:, 1), i) = count(:, 2);
end;
clearvars new;
disp('step2');

sum=0;
[hang3,lie3]=size(new2);
while(1)
    [C, row] = max(new2);
    [C2, col] = max(C);
    if C2==0
        break;
    else
        sum=sum+C2;
        row = row(col);
        col = col;
        new2(1:hang3, col)=0;
        new2(row, 1:lie3)=0;
    end;
end;
disp('step3');

accuracy=sum/total;
