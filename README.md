# UEFI-OS

## ファイル構成

- MikanLoaderPkg
    - UEFI アプリとして構成したブートローダ
- kernel
    - OS のカーネル
- resource/nihongo.ttf
    - IPA ゴシックのフォントファイル
- IPA_Font_License_Agreement_v1.0.txt
    - IPA フォントのライセンス文書

## ビルド方法

[EUFI-OS-build リポジトリ](https://github.com/murata0531/UEFI-OS-build.git) に OS をビルドするためのスクリプトがある。
EUFI-OS-build の手順に沿って開発ツールを導入した後、devenv/buildenv.sh を読み込むことでビルド可能。
（devenv/buildenv.sh により環境変数 CPPFLAGS などが適切に設定される。）


フォントファイルの変換

```
$ cd kernel/

$ python3 ../tools/makefont.py -o hankaku.bin hankaku.txt

$ objcopy -I binary -O elf64-x86-64 -B i386:x86-64 hankaku.bin hankaku.o
```


カーネルコンパイル&リンク

```
$ cd kernel 

$ make
```

実行

```
$ source build.sh run
```

