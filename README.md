# EUFI-OS

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

[EUFI-OS-build リポジトリ](https://github.com/murata0531/EUFI-OS-build.git) に OS をビルドするためのスクリプトがある。
EUFI-OS-build の手順に沿って開発ツールを導入した後、devenv/buildenv.sh を読み込むことでビルド可能。
（devenv/buildenv.sh により環境変数 CPPFLAGS などが適切に設定される。）

カーネルコンパイル&リンク

```
$ cd kernel 
```

build.shが失敗した場合↓

```
$ clang++ -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -std=c++17 -c main.cpp
```

build.shが成功した場合↓

```
clang++ -O2 $CPPFLAG --target=x86_64-elf -fno-exceptions -ffreestanding -c main.cpp
```

リンク
```
$ ld.lld --entry KernelMain -z norelro --image-base 0x100000 --static -o kernel.elf main.o
```

フォントファイルの変換

```
$ cd kernel/

$ ../tools/makefont.py -o hankaku.bin hankaku.txt

$ objcopy -I binary -O elf64-x86-64 -B i386:x86-64 hankaku.bin hankaku.o