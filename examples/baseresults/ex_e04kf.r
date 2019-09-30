nagcpp::opt::handle_solve_bounds_foas Example

 -------------------------------------------------------------------------------
  E04KF, First order method for bound-constrained problems                      
 -------------------------------------------------------------------------------
                                                                                                    
 Status: converged, an optimal solution was found                                                   
 Value of the objective             4.00000E-02                                                     
 Norm of inactive gradient          0.00000E+00                                                     
 Norm of projected direction        0.00000E+00                                                     
                                                                                
 Variables:                                                                     
     idx    lower bound       value       upper bound       gradient            
       1   -1.00000E+00    8.00000E-01    8.00000E-01   -4.00000E-01            
       2   -2.00000E+00    6.40000E-01    2.00000E+00    0.00000E+00            
Solution found: 
   Objective function value at solution:   4.0e-02

Monitoring Information:
 -------------------------------------------------------------------------------
  E04KF, First order method for bound-constrained problems                      
 -------------------------------------------------------------------------------
 Begin of Options                                                               
     Print File                    =                   6     * d                
     Print Level                   =                   1     * U                
     Print Options                 =                  No     * U                
     Print Solution                =                 All     * U                
     Monitoring File               =                  50     * U                
     Monitoring Level              =                   3     * U                
     Foas Monitor Frequency        =                   0     * d                
     Foas Print Frequency          =                   5     * U                
 
     Infinite Bound Size           =         1.00000E+20     * d                
     Task                          =            Minimize     * d                
     Stats Time                    =                  No     * d                
     Time Limit                    =         1.00000E+06     * d                
     Verify Derivatives            =                  No     * d                
 
     Foas Estimate Derivatives     =                  No     * d                
     Foas Finite Diff Interval     =         1.05367E-08     * d                
     Foas Iteration Limit          =            10000000     * d                
     Foas Memory                   =                  11     * d                
     Foas Progress Tolerance       =         1.08158E-12     * d                
     Foas Rel Stop Tolerance       =         1.08158E-12     * d                
     Foas Restart Factor           =         6.00000E+00     * d                
     Foas Slow Tolerance           =         1.01316E-02     * d                
     Foas Stop Tolerance           =         1.00000E-06     * d                
     Foas Tolerance Norm           =            Infinity     * d                
 End of Options                                                                 
                                                                                
 Problem statistics                                                             
     Number of variables                                       2                
     Number of free variables                                  0                
     Number of fixed variables                                 0                
     Number of variables with only lower bound                 0                
     Number of variables with only upper bound                 0                
     Number of variables with bounds                           2                
     Objective type                                    Nonlinear                
                                                                                                    
 -------------------------------------------------------------------------------                    
   iters |  objective |  optim  |   dir   | progrss | it|   step  |    nf|    ng                    
 -------------------------------------------------------------------------------                    
        0  8.50000E+01  1.80E+02  3.90E+00  1.00E+00       Start        1      1                    
        3  4.00000E+00  0.00E+00  1.80E+00  4.05E+01 NPG  1.00E+00      3      2                    
        5  3.99156E+00  2.80E+00  2.80E+00  7.05E-03     Switch CG     12      3                    
        7  3.97076E+00  5.76E+00  1.79E+00  6.84E-03  CG  6.24E-03     17      6                    
       12  1.97065E+00  6.49E+00  1.88E+00  5.66E-02 LCG  1.75E-01     29     13                    
       17  8.94996E-01  8.97E+00  2.02E+00  3.25E-01 LCG  1.41E+00     39     18                    
       22  2.51003E-01  2.68E+00  1.75E+00  2.54E-01 LCG  3.63E-01     52     27                    
       27  5.37636E-02  3.33E+00  1.80E+00  2.55E-01 LCG  3.25E-01     62     32                    
       28  4.02960E-02  3.44E-01  3.44E-01  1.59E-01 LCG  1.33E-01     65     34                    
       32  4.00000E-02  0.00E+00  0.00E+00  4.68E-03  CG  5.00E-03     75     36                    
 -------------------------------------------------------------------------------                    
 Status: converged, an optimal solution was found                                                   
 -------------------------------------------------------------------------------                    
 Value of the objective             4.00000E-02                                                     
 Norm of inactive gradient          0.00000E+00                                                     
 Norm of projected direction        0.00000E+00                                                     
 Iterations                                  32                                                     
 Function evaluations                        75                                                     
 FD func. evaluations                         0                                                     
 Gradient evaluations                        36                                                     
   NPG function calls                        18                                                     
   NPG gradient calls                         3                                                     
   CG function calls                          9                                                     
   CG gradient calls                          5                                                     
   LCG function calls                        48                                                     
   LCG gradient calls                        28                                                     
 -------------------------------------------------------------------------------                    
                                                                                
 Variables:                                                                     
     idx    lower bound       value       upper bound       gradient            
       1   -1.00000E+00    8.00000E-01    8.00000E-01   -4.00000E-01            
       2   -2.00000E+00    6.40000E-01    2.00000E+00    0.00000E+00            

