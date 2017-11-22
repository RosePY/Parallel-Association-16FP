#this code gnerate association and confidence values for two variables, serial
#setwd('/media/rose/New Volume/piba/ART1/ext/')
#source('codenp.R')
start.time <- Sys.time()
 binary=read.csv("CleanData.csv",header=FALSE)
 print(ncol(binary))
print(nrow(binary))
print("read")
comb=combn(163,2)

am=diag(NA,nrow=163)# matrix association
for(k in 1:ncol(comb))
{
	r=binary[comb[1,k]]& binary[comb[2,k]]
	am[comb[2,k],comb[1,k]]=sum(r)
}
print("p1")
am=am+t(am)	
write.csv(am, file = "assocFirst.csv", row.names = FALSE)
print("Matriz de asociacion escrita")

cm=diag(NA,nrow=163) #confidence matrix
# am=read.csv("assocFirst.csv",header=FALSE)
print(ncol(am))
print(nrow(am))
for(k in 1:ncol(comb))
{
s1=am[comb[2,k],comb[1,k]]/sum(binary[,comb[2,k]])
cm[comb[2,k],comb[1,k]]=s1
s2=am[comb[1,k],comb[2,k]]/sum(binary[,comb[1,k]])
 cm[comb[1,k],comb[2,k]]=s2
}
write.csv(cm, file = "ConfFirst.csv", row.names = FALSE)
print("Matriz de confidence escrita")

end.time <- Sys.time()
time.taken <- end.time - start.time
print(time.taken)