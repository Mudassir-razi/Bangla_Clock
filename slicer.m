image = imread('letterArray.png');
image = im2bw(image, 0.5);

imageNames = 'sNBrISm@lUdvhPTuCiQYjqAXRWbnKLkoGHeMzfgcOwtpayxV1234567890%{{D';

started = false;
leftBar = 1;
rightBar = 1;
counter = 1;

for i = 1:2 * length(imageNames)+1
    if started == true
        % check for blank line
        for j = leftBar + 1:length(image)
            if image(:, j) == 1
                % found the blank line
                fileName = imageNames(counter);
                if (imageNames(counter) >= 'A' && imageNames(counter) <= 'Z')
                    fileName = fileName + "_";
                end
                fileName = fileName + ".png";
                fullfileName = fullfile(pwd + "\output", fileName);
                counter = counter + 1;
                rightBar = j;
                started = false;
                im2 = image(:, leftBar:rightBar);
                im2 = imresize(im2, 0.15);
                imwrite(im2, fullfileName);
                break;
            end
        end
    else
        % check for non blank line
        for j = rightBar + 1:length(image)
            if sum(image(:, j) == 0) > 0
                %found non blank line
                leftBar = j;
                started = true;
                break;
            end
        end
    end
end

