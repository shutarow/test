test
====

test

##写真９６７枚の平均の検出率と誤検出率を閾値と窓の大きさを変更して求め、その値をcsv形式で出力するプログラム

#kzn
閾値
#wh
窓の大きさ

#61-79
正しい船舶位置のデータを読み込む

#81-108
読み込んだ写真を二乗の積分画像に変換している

#120-167
閾値を超えた窓を抽出し、同時に過去に抽出したものと重なっていたらそれと合成する

#171-202
船の先端部分がどうしても分散値が高いため、その部分で抽出した窓を削除している

#191-202
重なっている窓をもう一度探し、合成する

#206-219
正しい船舶の位置と窓を１つづつ比較する
shogo:あっていた数
rtat:正しい船舶数
tat:抽出した窓の数