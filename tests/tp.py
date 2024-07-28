# Aucun n'import ne doit être fait dans ce fichier

def number_int(n: int) -> str:
    if (n==0):
        return "0"
    else:
        string = ""
        for i in range(n):
            string+="S"
        string+="0"
    return string

def S(n: str) -> str:
    if (n=="0"):
        return "S0"
    else:
        i = 0
        string=""
        while i <= len(n)-1:
            string+="S"
            i+=1
        string+="0"
    return string


def addition(a: str, b: str) -> str:
    if a == "0" and b == "0":
        return "0"
    elif a == "0":
        return b
    elif b == "0":
        return a
    else:
        string = ""
        i = 0
        print(type(a))
        while i <= len(a)-2:
            string+="S"
            i+=1
        i=0
        while i <= len(b)-2: 
            string+="S"
            i+=1
        string+="0"
        return string


def multiplication(a: str, b: str) -> str:
    if a == "0" or b=="0":
        return "0"
    elif a == "S0":
        return b
    elif b =="S0":
        return a
    else:
        string = a[:-1]
        i = 0
        while i <= len(b)-3: 
            string+=a[:-1]
            i+=1
        string+="0"
        return string

def facto_ite(n: int) -> int:
    if n == 0:
        return 1
    else:
        result = 1
        for i in range(2,n+1):
            result = result * i
        return result

def facto_rec(n: int) -> int:
    if n == 0:
        return 1
    else:
        return n  * facto_rec(n-1)


def fibo_rec(n: int) -> int:
    if n <= 0:
        return 0
    elif n == 1 or n==2:
        return 1
    else:
        return fibo_rec(n - 1) + fibo_rec(n - 2)


def fibo_ite(n: int) -> int:
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        a, b = 0, 1
        for i in range(2, n + 1):
            c = a
            a = b
            b = c + b
        return b


def golden_phi(n: int) -> int:
    pass


def sqrt5(n: int) -> int:
    pass


def pow(a: float, n: int) -> float:
    pass
