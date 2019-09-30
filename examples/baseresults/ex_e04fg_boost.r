nagcpp::opt::handle_solve_dfls_rcomm Example
  ---------------------------------------------------                           
  E04F(G|F)), Derivative free solver for data fitting                           
              (nonlinear least-squares problems)                                
  ---------------------------------------------------                           
                                                                                
  Problem statistics                                                            
    Number of variables                  2                                      
    Number of unconstrained variables    0                                      
    Number of fixed variables            0                                      
    Starting interpolation points        3                                      
    Total interpolation points           3                                      
    Number of residuals                  2                                      
                                                                                
 Begin of Options                                                               
     Print File                    =                   6     * d                
     Print Level                   =                   2     * d                
     Print Options                 =                 Yes     * d                
     Print Solution                =                 All     * U                
     Monitoring File               =                  -1     * d                
     Monitoring Level              =                   4     * d                
     Dfo Print Frequency           =                   1     * d                
     Dfo Monitor Frequency         =                   0     * d                
 
     Infinite Bound Size           =         1.00000E+20     * d                
     Stats Time                    =                  No     * d                
     Time Limit                    =         1.00000E+06     * d                
 
     Dfo Initial Interp Points     =          Coordinate     * d                
     Dfo Max Objective Calls       =                 500     * d                
     Dfo Max Soft Restarts         =                   5     * d                
     Dfo Max Unsucc Soft Restarts  =                   3     * d                
     Dfo Maximum Slow Steps        =                  20     * d                
     Dfo Noise Level               =         0.00000E+00     * d                
     Dfo Noisy Problem             =                  No     * d                
     Dfo Number Initial Points     =                   0     * d                
     Dfo Number Interp Points      =                   0     * d                
     Dfo Number Soft Restarts Pts  =                   3     * d                
     Dfo Random Seed               =                  -1     * d                
     Dfo Starting Trust Region     =         1.00000E-01     * d                
     Dfo Trust Region Slow Tol     =         1.02648E-04     * d                
     Dfo Trust Region Tolerance    =         5.00000E-06     * U                
     Dfo Version                   =              Latest     * d                
     Dfls Small Residuals Tol      =         1.08158E-12     * d                
 End of Options                                                                 
  ----------------------------------------                                      
   step |    obj        rho    |    nf   |                                      
  ----------------------------------------                                      
      1 |  4.02E+00  1.00E-01  |     4   |                                      
      2 |  3.66E+00  1.00E-01  |     5   |                                      
      3 |  3.48E+00  1.00E-01  |     6   |                                      
      4 |  2.32E+00  1.00E-01  |     9   |                                      
      5 |  1.94E+00  1.00E-01  |    10   |                                      
      6 |  1.63E+00  1.00E-01  |    12   |                                      
      7 |  9.65E-01  1.00E-01  |    14   |                                      
      8 |  7.29E-01  1.00E-01  |    16   |                                      
      9 |  4.77E-01  1.00E-01  |    19   |                                      
     10 |  1.29E-01  1.00E-01  |    21   |                                      
     11 |  5.70E-02  1.00E-01  |    23   |                                      
     12 |  2.21E-04  1.00E-01  |    25   |                                      
     13 |  1.28E-04  1.00E-02  |    26   |                                      
     14 |  1.36E-08  1.00E-03  |    28   |                                      
     15 |  1.03E-23  5.00E-06  |    32   |                                      
  ----------------------------------------                                      
  Status: Converged, small residuals                                            
                                                                                
  Value of the objective                    1.03447E-23                         
  Number of objective function evaluations           32                         
  Number of steps                                    15                         
                                                                                
                                                                                
 Primal variables:                                                              
   idx   Lower bound        Value      Upper bound                              
     1  -1.50000E+00    1.00000E+00    2.00000E+00                              
     2  -2.00000E+00    1.00000E+00         inf                                 
