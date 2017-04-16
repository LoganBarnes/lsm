
maxIterations = 30;
errorThreshold = 1.0e-8;

% initialize the matrix
A = [ [ 10., -1., 2., 0.  ];
      [ -1., 11., -1., 3. ];
      [ 2., -1., 10., -1. ];
      [ 0.0, 3., -1., 8.  ] ];
  
% initialize the RHS vector
b = [6.; 25.; -11.; 15.];


disp( A );
disp( b );

x = zeros( size( b ) );

rows = size( A, 1 );
cols = size( A, 2 );

L = tril( A, 0 );
U = triu( A, 1 );

T = -L \ U;
C = L \ b;

for iter = 1:maxIterations

    disp( [ int2str(iter), ': ', mat2str(x') ] );
        
    x_new = T * x + C;

    if nnz( abs( x - x_new ) < errorThreshold ) == cols
       break; 
    end
    
    x = x_new;
    
end

x = round( x );

y = A \ b;

disp( [ 'Actual: ', mat2str(y') ] );

