set.seed(123)
A <- replicate(4, rnorm(1000000))
apply( A, 2, mean)
apply( A, 2, var)
write.table(t(A), file="aov.txt", quote = FALSE, row.names = FALSE, col.names = FALSE )
colnames(A) <- c("X","Y","Z","W")
O <- A[0:100, 0:4]
A <- O
T <- as.data.frame(A)
T
res.aov <- aov( X ~ Y, data = T )
summary(res.aov)
mean(A[,1], trim = 0, na.rm = FALSE)
var(A[,1])

mean(A[,2], trim = 0, na.rm = FALSE)
var(A[,2])
