# UEFI-OS

## OSについての基礎知識

https://hackmd.io/imuvwGTJQ3-3YkBT0Zh4Qw

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

[UEFI-OS-build リポジトリ](https://github.com/murata0531/UEFI-OS-build.git) に OS をビルドするためのスクリプトがある。
UEFI-OS-build の手順に沿って開発ツールを導入した後、devenv/buildenv.sh を読み込むことでビルド可能。
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

# コマンド群

| コマンド名                               | 説明                                  |
|------------------------------------------|---------------------------------------|
| ls [対象ディレクトリ]                    | ディレクトリ内のファイルを表示する     |
|                                          |                                       |
| lspci                                    | 接続しているデバイスを表示する         |
|                                          |                                       |
| cat [対象ファイル]                       | ファイル内の文字列を表示する           |
|                                          |                                       |
| more [対象ファイル]                      | ページ単位でファイルの内容を表示       |
|                                         |                                        |
| grep [検索文字列] [対象ファイル]         | 文字列検索                             |
|                                         |                                        |
| cp [コピー元ファイル] [コピー先ファイル] | ファイルコピー                         |
|                                         |                                        |
| echo [コマンドまたは文字列]              | 文字列を出力                           |
|                                         |                                        |
| noterm [アプリケーション]                | アプリ実行時にターミナルを占有しない    |
|                                         |                                        |
| clear                                   | ターミナルをクリア                     |
|                                         |                                        |
| rpn [計算式]                       　   |  逆ポーランド記法で計算する             |
|                                         |                                        |
| [コマンド1] \| [コマンド2]　           　| コマンド1の出力をコマンド2に渡す       |
|                                         |                                        |
| [コマンド] > [ファイル]               　 | コマンドの結果をファイルに保存する     |
|                                         |                                        |
| F2キー                                  | 新規ターミナルを立ち上げる              |
|                                                                                  |
