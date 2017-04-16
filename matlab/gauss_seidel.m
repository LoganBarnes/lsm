
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

for iter = 1:maxIterations

    disp( [ int2str(iter), ': ', mat2str(x') ] );
    x_new = zeros( size( x ) );
        
    for i = 1:rows
        s1 = A( i, 1:i ) * x_new( 1:i );
        s2 = A( i, i+1:cols )* x( i+1:rows );
        x_new( i ) = ( b( i ) - s1 - s2 ) / A( i, i );
    end
    
    if nnz( abs( x - x_new ) < errorThreshold ) == cols
       break; 
    end
    
    x = x_new;
    
end

x = round( x );

y = A \ b;

disp( [ 'Actual: ', mat2str(y') ] );

