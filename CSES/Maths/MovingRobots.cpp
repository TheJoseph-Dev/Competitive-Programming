/*
    Absolutely — this is a great opportunity to understand **expected value** more deeply, especially in the context of **random processes** like this one.

Let's build your intuition from the ground up and then connect it directly to your chessboard problem.

---

## 💡 What Is Expected Value?

In words, **expected value** is the **long-run average** outcome of a random experiment if you repeated it over and over.

Let’s say you roll a die. The expected value of the result is:

$$
E = \sum_{i=1}^6 \text{(value of outcome)} \times \text{(probability of outcome)} = \sum_{i=1}^6 i \cdot \frac{1}{6} = 3.5
$$

It’s not saying you'll roll a 3.5 — it's saying that **on average**, over many rolls, the average result converges to 3.5.

---

## ✅ Applying That to This Problem

### 🎯 Question Restated:

> After $k$ steps, what is the **expected number of empty squares** on the 8×8 board?

Each robot moves randomly. After $k$ steps, multiple robots might land on the same square, and some squares might be unoccupied. You want to compute the **average number of empty squares** after all robots have moved.

This is a classic case where **linearity of expectation** is super helpful.

---

## 🧠 Key Principle: **Linearity of Expectation**

This says:

> The expected value of a **sum of random variables** is equal to the **sum of their expected values**, no matter whether they are independent or not.

Formally:

$$
\mathbb{E}[X_1 + X_2 + \dots + X_n] = \mathbb{E}[X_1] + \mathbb{E}[X_2] + \dots + \mathbb{E}[X_n]
$$

You don’t need the variables to be independent. That’s huge.

---

## 🧮 Step-by-Step Plan Using Linearity

### Step 1: Define indicator random variables

Let’s define a variable for **each square**:

$$
I_{r,c} = 
\begin{cases}
1 & \text{if square } (r, c) \text{ is empty after } k \text{ steps} \\
0 & \text{otherwise}
\end{cases}
$$

This is a **random variable**: it’s 1 or 0 depending on whether the square ends up empty or not.

Then the total number of empty squares is:

$$
\text{Empty}(k) = \sum_{r=0}^7 \sum_{c=0}^7 I_{r,c}
$$

The expected number of empty squares is:

$$
\mathbb{E}[\text{Empty}(k)] = \sum_{r=0}^7 \sum_{c=0}^7 \mathbb{E}[I_{r,c}]
$$

But each $\mathbb{E}[I_{r,c}]$ is just:

$$
\mathbb{E}[I_{r,c}] = \mathbb{P}(\text{square } (r,c) \text{ is empty})
$$

So now the question becomes:

> What is the probability that **no robot ends up at square $(r,c)$** after $k$ moves?

---

### Step 2: Computing $\mathbb{P}(\text{square } (r,c) \text{ is empty})$

There are 64 robots, one on each square at the start. They all move independently, and any of them might land at $(r,c)$.

Let’s denote:

* $p_{r_0, c_0}^{(r, c)}$: the probability that the robot that started at $(r_0, c_0)$ is at $(r,c)$ after $k$ moves.

So, for a fixed square $(r, c)$, the probability it is empty is:

$$
\mathbb{P}(\text{square } (r, c) \text{ is empty}) = \prod_{(r_0, c_0)} \left(1 - p_{r_0, c_0}^{(r, c)}\right)
$$

Because for the square to be empty, **none** of the robots must be at that square — so we multiply the probabilities that each **individual robot** is **not** there.

---

## 🎯 Final Expected Value Formula

$$
\mathbb{E}[\text{number of empty squares}] = \sum_{(r,c)} \prod_{(r_0,c_0)} \left(1 - p_{r_0, c_0}^{(r, c)}\right)
$$

That’s your final expression, now rooted in expected value theory.

---

## 🔁 Summary of Concepts You Just Learned

| Concept                             | Meaning                                                                                                                        |
| ----------------------------------- | ------------------------------------------------------------------------------------------------------------------------------ |
| **Expected Value**                  | Long-run average outcome of a random variable                                                                                  |
| **Indicator Variables**             | 0-1 variables to track specific outcomes (like whether a square is empty)                                                      |
| **Linearity of Expectation**        | You can sum expected values of parts to get total expected value, no matter independence                                       |
| **Multiplication of Probabilities** | To get probability that **no robot** is at a square, multiply the complements of their individual probabilities of being there |

*/

#include <stdio.h>

int k;
double dp[101][8][8][8][8];
void fill() {
    //memset(dp, 0, sizeof(dp));
    for(int a = 0; a < 8; a++)
        for(int b = 0; b < 8; b++)
            dp[0][a][b][a][b] = 1;
    
    for(int s = 1; s <= k; s++)
        for(int a = 0; a < 8; a++)
            for(int b = 0; b < 8; b++)
                for(int i = 0; i < 8; i++)
                    for(int j = 0; j < 8; j++) {
                        if(((i+j)&1) != ((a+b+s)&1)) continue;
                        int cnt = (i!=0)+(i!=7)+(j!=0)+(j!=7);
                        double p = 0;
                        if(i != 0) p += dp[s-1][a][b][i-1][j];
                        if(i != 7) p += dp[s-1][a][b][i+1][j];
                        if(j != 0) p += dp[s-1][a][b][i][j-1];
                        if(j != 7) p += dp[s-1][a][b][i][j+1];
                        dp[s][a][b][i][j] = p/cnt;
                    }
}

double expected() {
    double exp = 0;
    for(int a = 0; a < 8; a++)
        for(int b = 0; b < 8; b++) {
            double empty = 1;
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 8; j++)
                    empty *= (1-dp[k][a][b][i][j]);
            exp += empty;
        }

    return exp;
}

int main() {
    scanf("%d", &k);
    fill();
    printf("%.6lf\n", expected());
    return 0;
}