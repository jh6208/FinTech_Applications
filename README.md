# [NYU Tandon FRE-68833 Song Tang] FinTech_Applications

<img width="1171" alt="截屏2023-12-24 下午8 10 15" src="https://github.com/jh6208/FinTech_Applications/assets/122949623/d2a45d19-e59e-406f-8fa1-ff874082b81e">


The C++ projects are designed to address complex problems in financial technology through the application of computational finance models and algorithms. These projects include:

***1. Assignment_1_Binomial_Tree_Model_Factorial:*** 

This first assignment uses an alternate method to calculate the prices of the European call options using the Cox-Ross-Rubinstein (CRR) procedure. 

* Category: Concept Teachings (Functions)

***2. Assignment_2_Call_Put_Prices:*** 

This second assignment calculates the prices of European calls and puts and the digit calls and puts using the CRR procedure. 

* Category: Concept Teachings (Functions)

***3. Assignment_3_Definite_Integrals:***

This assignment calculates the definite integral using the Simpson and Trapezoid approaches.

* Category: Concept Teachings (Classes & Functions)

***4. Assignment_4_More_Option_Prices:***

This short exercise calculates the prices of bulls and spreads using the CRR procedure.

* Category: Concept Teachings (Polymorphism & Classes & Functions)

***5. Assignment_5_More_Option_Prices:***

This short exercise calculates the prices of the double-digit options, strangle, and butterflies.

* Category: Concept Teachings (Polymorphism & Classes & Functions)

***6. Assignment_6_American_Options_Replication_Strategy:***

Assignment 6 calculates the prices of American options using the replication approaches.

* Category: Concept Teachings (Template & Data Structures & Polymorphism & Classes & Functions)

***7. Assignment_7_Black_Scholes_Introduction:***

This assignment aims to approximate the results of the Black Scholes (BS) model using the binomial tree model.

* Category: Concept Teachings (Template & Data Structures & Polymorphism & Classes & Functions)

***8. Assignment_8_Bond_Yield_Calculation:***

This assignment calculates the yield of semi-annual coupon bonds using the Bisection and Newton-Raphson methods.

* Category: Concept Teachings (Multiple Inheritance & Classes & Functions)

***9. Assignment_9_European_Options_Financial_Applications:***

This exercise edits the original version of Daniel Duffy's book, Introduction to C++ for Financial Engineers, for calculating European Option options with the BS formula.

* Category: Financial Applications

***10. Assignment_10_Asian_Options_Gamma_Determination:***

This exercise calculates the gamma of the Asian calls using the Monte Carlo simulation approach.

* Category: Concept Teachings (Monte Carlo Simulations & Data Structures Definition & Data Structures & Polymorphism & Classes & Functions)

***11. Assignment_10_Asian_Option_Prices_Improved:***

This assignment reduces the pricing error of the Asian calls by using the control-variable approaches.

* Category: Concept Teachings (Monte Carlo Simulations & Data Structures Definition & Data Structures & Polymorphism & Classes & Functions)

***12. Assignment_10_Basket_of_Asian_Option_Prices_Determination:***

This last assignment applies the Monte Carlo method to calculate the prices of a basket of Asian call options.

* Category: Concept Teachings (Monte Carlo Simulations & Data Structures Definition & Data Structures & Polymorphism & Classes & Functions)
  
***13. Final_Project_CAAR_Finance:***

This final project is a hands-on application in the financial technology field. It investigates the quarterly reports’ impact on stock market trends. It first fetches data using the libcurl library to access the daily adjusted prices of Russell 300 Component stocks. Then it calculates the daily log returns, cumulative returns, abnormal returns (AR) using IWV index as the benchmark), the average of AR (AAR), AAR Std, Cumulative AAR (CAAR), and CAAR Std by bootstrapping these stocks and by repeating the procedure of randomly selecting 30 stocks 40 times for each group (i.e, beat, meet, and miss groups based on the ordering of the surprise% in the earning announcement file Russell3000EarningsAnnouncements.csv). Finally, it plots the CAAR graph for each group (Note: the x-axis is time ranging from N days before and after the earning announcement day for each component stock, and N is no less than 60 and no bigger than 90 days).
