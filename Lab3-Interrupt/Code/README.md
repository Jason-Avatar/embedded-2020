# Embedded Systems @ NCKU EE

## Github link
https://github.com/rtes-ncku/embedded-2020

## Directory structure and file names
![](https://i.imgur.com/VjYTriL.png)

- src: 
	source code，請不要修改此處內容。
- result_sample: 
	測試用執行檔，可用於瞭解結果應如何呈現。
- code: 
	執行 set_env.sh 後產生，請修改此資料夾內容以符合題目要求。
- bin: 
	make後編譯產出的執行檔，用於驗證程式是否能正常運行且符合要求。
- README: 
	實驗須知。
- set_env.sh: 
	初始化環境用。
- check_file.sh: 
	檢查檔案是否完整 (助教用)。
- clear_set.sh: 
	清除產生的 code 與 bin 資料夾內容，以方便快速重設 (如需保留修改後內容，記得要先備份)。
- Makefile 

## Instructions

### Building

Requirements:
* libmraa
* GNU Make
* GCC

1. Initialize development environment
初始化開發環境
```
sh set_env.sh
```
執行完上述指令後應產生出 code 資料夾與其內容

2. Compile modified code
依需求編譯所需之程式碼
```
# build everything
make all
# build selected file
make bin/06
```
編譯位於 code 資料夾內的程式，並透過 scp 指令將執行檔傳輸至 Up board 上等待執行

3. Running
執行程式
```
sudo bin/06
```
注意: 需使用 **sudo** 權限才能正常運行程式


```
scp -r em_up:/lib/modules/5.4.0-1-generic/ ~
sudo mv ~/5.4.0-1-generic/ /lib/modules
```
