#! /bash/sh

ffmpeg -i icon1.png -vf scale=128:128:flags=neighbor -pix_fmt pal8 middle_icon0.png
pngquant middle_icon0.png -o icon2.png
rm -f middle_icon0.png

cd livearea/contents

ffmpeg -i bg1.png -vf scale=840:500:flags=neighbor -pix_fmt pal8 middle_bg0.png
pngquant middle_bg0.png -o bg0.png
rm middle_bg0.png
