%Nicholas Schroeder

close all;
clear all;
clc;

part1 = 0;
part2 = 1;

if part1 == 1
    %OPTIMAL REFRESH PARAMETERS
    ref = [1,5,10,25,50,100,200,500,1000,5000,10000];

    %Figure 
    pf_10 = [59292,22809,17996,16920,16611,16745,16809,17988,18839,34879,40227];
    pf_50 = [35299,15521,11317,5060,3212,1628,1009,613,528,470,495];
    pf_100 = [3953,2655,2269,1734,1153,746,625,440,417,394,381];

    plot(ref,pf_10);
    hold on;
    plot(ref,pf_50);
    hold on;
    plot(ref,pf_100);
end

%BEST ALGORITHM
if part2 == 1
   figure(1);
   
   ref = [10,50,100];
   
   opt_pf = [8820,346,294];
   fifo_pf = [22916,728,294];
   age_8_pf = [18174,12639,2333];
   age_16_pf = [17068,9213,2081];
   age_32_pf = [17001,4369,1467];
   age_64_pf = [16512,2486,995];
   
   plot(ref,opt_pf);
   hold on;
   plot(ref,fifo_pf);
   hold on;
   plot(ref,age_8_pf);
   hold on;
   plot(ref,age_16_pf);
   hold on;
   plot(ref,age_32_pf);
   hold on;
   plot(ref,age_64_pf);
   
   figure(2);
   
   ref = [10,50,100];
   
   opt_pf = [3049,146,102];
   fifo_pf = [9057,355,184];
   age_8_pf = [3670,1506,149];
   age_16_pf = [4528,1080,149];
   age_32_pf = [5060,618,127];
   age_64_pf = [5078,430,99];
   
   plot(ref,opt_pf);
   hold on;
   plot(ref,fifo_pf);
   hold on;
   plot(ref,age_8_pf);
   hold on;
   plot(ref,age_16_pf);
   hold on;
   plot(ref,age_32_pf);
   hold on;
   plot(ref,age_64_pf);
end
