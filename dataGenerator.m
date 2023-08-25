xoffset = 0;
yoffset = 0;
cursorList = [10 15 20 10];

indexer = "";
bitmap = "";

defaultData = sprintf('{0, 0, 0, 5, 0, 1}');
imageNames = "sNBrISm@lUdvhPTuCiQYjqAXRWbnKLkoGHeMzfgcOwtpayxV1234567890%{{DE";

letterGroup1 = "vsmldhYbnhoezOpxUgyPuCRG";
letterGroup2 = "NBITiQjqAXWKLHMfctaVD";
letterGroup3 = "SwE";

asciiStart = 32;
asciiEnd = 126;
offset = 0;
hexFile = fopen('C:\Users\koomf\Documents\Arduino\test\CustomBangla.h', 'w');

for i = asciiStart: asciiEnd
    
    currentLetter = char(i);
    %determining letter offset
    lg = 4;
    if contains(letterGroup1, currentLetter)
        lg = 1;
    elseif contains(letterGroup2, currentLetter)
        lg = 2;
    elseif contains(letterGroup3, currentLetter)
        lg = 3;
    end
    %

    if contains(imageNames, currentLetter)
        %push data for this character
        letterName = char(i);
        if i >= 'A' && i <= 'Z'
            letterName = letterName + "_";
        end
        
        letter = imread("output\" + letterName + ".png");
        data = sprintf('{%d, %d, %d, %d, %d, %d}, //%s\n', offset, width(letter), height(letter), cursorList(lg), xoffset, yoffset, letterName);
        indexer = indexer + data;
        offset = offset + (width(letter) * height(letter))/8;
        
        hex = "";
        %generating the bitmap 
        letter = letter';
        letter = reshape(letter, [1, width(letter) * height(letter)]);
        letter = abs(1 - letter);
        chunkCount = 0;
        for j = 1:8:length(letter)-7
            chunkStr = num2str(letter(j:j+7));
            chunk = bin2dec(chunkStr);
            chunkCount = chunkCount + 1;
            prefix = "0x";
            if chunk < 16
                prefix = prefix + "0";
            end
            hex = hex + prefix +  num2str(dec2hex(chunk)) + ", ";
        end
        disp(chunkCount);
        bitmap = sprintf(' %s \n', bitmap, hex);
    else
        %push default data
        indexer = indexer + defaultData;
        if i ~= asciiEnd
            indexer = indexer + ",";
        end
        indexer = sprintf("%s\n", indexer);
    end
end

bitmap = strtrim(bitmap);
fprintf(hexFile, '#pragma once \n #include <Adafruit_GFX.h> \n\n const uint8_t CustomBanglaBitmaps[] PROGMEM = { %s };\n\n const GFXglyph CustomBanglaGlyphs[] PROGMEM = {%s};\n\nconst GFXfont CustomBangla PROGMEM = {(uint8_t *)CustomBanglaBitmaps,\n(GFXglyph *)CustomBanglaGlyphs, 0x20, 0x7E, 16};'...
                , bitmap(1, 1:end-1), indexer);

fclose(hexFile);

