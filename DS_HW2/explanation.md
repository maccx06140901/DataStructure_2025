
---

## 🧩 一、為什麼要轉成前序？

在中序表示式中（例如 `3 + 4 * 2`），  
我們需要同時考慮 **運算子優先權** 以及 **括號**。  
也就是說：
- `*` 和 `/` 的優先權比 `+` 和 `-` 高；
- 括號又可能改變原本的順序。

這使得「邊讀邊算」的過程很複雜。

而前序 (Prefix) 的特點是：
- 運算子永遠在它的兩個運算元前面；
- 優先權與括號的資訊已經被轉換過程決定；
- 所以在求值階段只需 **一個堆疊 (stack)** 就能完成計算。

> 💡 簡單說：  
> **把「誰先算」的邏輯提前處理好，計算就變成純機械操作。**

---

## ⚙️ 二、演算法流程（Shunting-yard 建樹法）

1. **準備兩個堆疊：**
   - `op_stack`：存放運算子；
   - `node_stack`：存放節點（數字或子樹）。

2. **從左到右掃描 token：**
   - 若為數字：建立葉節點推入 `node_stack`
   - 若為 `(`：推入 `op_stack`
   - 若為 `)`：  
     - 不斷彈出 `op_stack` 直到遇到 `(`  
     - 每次彈出運算子時，從 `node_stack` 取兩棵子樹建立新節點再推回。
   - 若為運算子：
     - 只要堆頂的運算子優先權高於或等於目前的運算子，  
       就先處理堆頂（建立節點）；
     - 然後再把目前運算子推入 `op_stack`。

3. **處理剩餘堆疊：**
   - 當輸入讀完後，把 `op_stack` 中剩餘運算子依序彈出並建樹。

4. **最後 `node_stack` 只剩一棵樹，就是完整的運算樹。**

---

## 🧮 三、運算樹求值

採用遞迴求值：
```c
int cal(Node* root) {
    if (root == NULL) return 0;
    if (root->is_num == 1) return root->num;
    int left  = cal(root->left);
    int right = cal(root->right);
    switch (root->ch) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right; // 整數除法
    }
    return 0;
}
