set.seed(123)
A <- replicate(4, rnorm(1000000))
apply( A, 2, mean)
apply( A, 2, var)
write.table(t(A), file="aov.txt", quote = FALSE, row.names = FALSE, col.names = FALSE )