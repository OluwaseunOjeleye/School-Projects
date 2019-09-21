class BooleanFunction():
	
	def __init__(self,List):
		##Getting maximum minterm(number) in list
		max_no=max(List)	
		##Getting no of binary bits/variables for greatest number
		self.variables=len("{0:b}".format(max_no)) 
		self.List=List
		self.EI=[]

	## Main Method for minimization
	def minimize(self):
		L=self.BinlistConverter(self.List,self.variables)
		self.SpecialPrint(L)
		self.SpecialPrint(self.Reduction(L))
		self.simplifywithRule(L)
		print()

	# getting boolean variables in string form
	def getBooleanVar(self):
   		string=list()
   		variables=["x1","x2","x3","x4","x5","x6","x7","x8"]
   		for i in range(self.variables):
   			string.append(variables[i])
   		return variables

   	#Binary number Converter
	def BinConverter(self,decimal):
		binary=""
		while(decimal!=0):
			r=decimal%2
			decimal=decimal//2
			binary=str(r)+binary
		return binary

	## adding 0 at front of binary if it has less bits
	def addZeroAtFront(self, binary,VarNo):
		for i in range (VarNo-len(binary)):
			binary="0"+binary
		return binary

	## Method for converting a list with number to binary list
	##Example F=[0,1,2,4,6] converted to F=["000","001","010","100","101"]
	def BinlistConverter(self,decimallist,VarNo):
		binList=[]
		for i in range (len(decimallist)):
			b=self.addZeroAtFront(self.BinConverter(decimallist[i]),VarNo)
			binList.append(b)
		return binList

	## Method for checking if two binaries differ in only one bit
	def isGrayCode(self, binary1,binary2):
		count=0
		for i in range (self.variables):
			if(binary1[i]!=binary2[i]):
				count=count+1
		if(count==1):
			return True
		else:
			return False

	## Method for simplifying two binary numbers
	## Example 000 and 001 will be simplified to 00-
	def changeComplements(self, binary1, binary2):
		term=""
		for i in range (self.variables):
			if(binary1[i]!=binary2[i]):
				term=term+"-"
			else:
				term=term+binary1[i]
		return term

	## Method for returning n-bit of dashes E.g "---"
	def emptydashes(self):
		s=""
		for i in range (self.variables):
			s=s+"-"
		return s

	## Method for reducing a Function to its first reduction only(It's for showing more steps)
	## This Method determines if F=1 too
	def Reduction(self, mintermslist):
		Exp=[]
		List=mintermslist.copy()
		for i in range (len(List)):
			for j in range (len(List)):
				if(i!=j):
					if(List[i]!=self.emptydashes()):
						if(self.isGrayCode(List[i],List[j])):
							Exp.append(self.changeComplements(List[i],List[j]))
							List.remove(List[i])
							List.insert(i,self.emptydashes())
							List.remove(List[j])
							List.insert(j,self.emptydashes())
		Exp=Exp+List
		L=[]
		for i in range (len(Exp)):
			if (Exp[i]!=self.emptydashes()):
				L.append(Exp[i])
		return L

	##Minimization Of terms is done on tablehere
	##It's Like a Table... It is filled with minterms
	def Minimizer(self, List):
		MT=[]
		if(len(List)>1):
			for i in range(len(List)):
				MT.append([])
				for j in range(len(List)):
					if(i!=j):
						if(self.isGrayCode(List[i],List[j])):
							MT[i].append(self.changeComplements(List[i],List[j]))
						else:
							MT[i].append(self.emptydashes())
					else:
						MT[i].append(self.emptydashes())
			return MT
		else:
			return List

	## Computing Prime Implicants on an already filled Matrix MT
	def getPrimeImplicants(self, MT):
		PI=[]
		if(len(MT)>1):
			for i in range (len(MT[0])):
				for j in range (len(MT[0])):
					if(MT[i][j]!=self.emptydashes()):
						PI.append(MT[i][j])

			##removing duplicates of prime implicants.
			PI=list(set(PI))
			if(len(PI)==0):
				return 0
			else:
				return PI
		else:
			return 0

	## Computing Essential Implicants on an already filled Matrix MT
	def getEssentialImplicants(self, List, MT):
		EI=[]
		if(len(MT)>1):
			for i in range (len(MT[0])):
				c=0
				for j in range (len(MT[0])):
					if(MT[i][j]==self.emptydashes()):
						c=c+1
				if(c==len(MT[0])):
					EI.append(List[i])
			return EI
		else:
			return List

	## This Is the method that do all the minimization using the above Methods...
	## It uses recursion by simplifying and printing every newly minimized expression until it gets to the last one
	def simplifywithRule(self,mintermslist):
		#print("MinTerm is: ",mintermslist)
		F=[]
		T=self.Minimizer(mintermslist)
		self.EI=self.EI+self.getEssentialImplicants(mintermslist, T)	##Essential Implicant
		PI=self.getPrimeImplicants(T)	##Prime Implicants

		## Keeping all minterms from EI and PI in a list called F
		if (PI!=0):
			F=self.EI+PI
		else:
			F=self.EI

		## Showing More steps using Reduction Method
		E=self.Reduction(F)
		## There must always be elements returned back to List E else F=1 
		if(len(E)!=0):
			if(sorted(F)==sorted(E)):
				self.SpecialPrint(F)
			else:
				self.SpecialPrint(F)
				self.SpecialPrint(E)
		##Because E is Empty then F=1
		else:
			print("\nF=1")

		## Continue recursion by simplifying PI until we have no PI anymore
		while(PI!=0):
			return self.simplifywithRule(PI)


	## Special Method for printing 
	def SpecialPrint(self, F):
		print("\nF=", end=" ")
		for i in range (len(F)):
			if(F[i]!=self.emptydashes()):
				print(self.Convert_minterm_variable(F[i]), end=" ")
				#print(F[i])
			if(i!=(len(F)-1)):
				print("+",end=" ")
		return 0

	## Method for converting binary minterms to string form...
	## Example (00- is A`B`)  and  (1011 is AB`CD)
	def Convert_minterm_variable(self, boolVar):
		temp=""
		variables=self.getBooleanVar()
		for i in range (len(boolVar)):
			if(boolVar[i]!="-"):
				if(boolVar[i]=="0"):
					temp=temp+variables[i]+"\'"
				else:
					temp=temp+variables[i]
		return temp


def main():
	###	Testing...
	##l=[0,1,4,5,8,9,12,13]

	print("Input Minterms: (Example- 0 1 4 5 8 9 12 13)")
	l=[int(i) for i in input().split()]


	F=BooleanFunction(l).minimize()
	print("Function Simplified...........")
	
main()


	
		