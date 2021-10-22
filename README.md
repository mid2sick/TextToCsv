# TextToCsv
Read the chinese text and write the selected context into a csv file

## Steps

1. 從 csv 中把所有名字讀起來存進陣列
2. 開一個新的 csv 並把原本的欄位名稱複製過去
3. 在 txt 中透過 [number].[name] 去找對應的資料
4. 找到內容、關鍵字跟參考資料後存在對應的變數
   - 參考資料因為行數不固定，所以適用迴圈存直到遇到下一個 [number].[name] 或是進入到下一個段落像是 [A2…]
5. 把原 csv 的前幾個已有資料的欄位跟得到的變數一起寫進新的 csv 檔
