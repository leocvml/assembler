# line  Label   Instr   Para            => INSFromL
# 1             LDX     #32
# 2     AAA     LDX     KKBOX
def hexi(List): #int
    Delx = []
    for i in List:
        Delx.append(i[2:])
    return Delx
def fit6(opcode):
    new_opcode =[]
    for i in opcode:
        if len(i) < 6 and i !=' ':
            fit0 = "000000"
            fit0 = fit0[0:6-len(i)]+i
            new_opcode.append(fit0)
        else:
            new_opcode.append(i)      
    return new_opcode
def Out_txt(LocCounter,INSFromL,Op):
    file = open('asm_out.txt','w')
    txt_Line = range(len(INSFromL))
    for i in txt_Line:
        file.write(LocCounter[i]+"\t"+INSFromL[i][0] +"\t" + INSFromL[i][1]+"\t" +INSFromL[i][2]+"\t" + INSFromL[i][3]+"\t"+Op[i]+"\n")
      
    file.close()
    
def run(filename):
    LabelsP3 = ['LDA','LDB','LDX','ADD','JSUB','JEQ','STA','TIX','RSUB','J','JLT','WORD','END']
    P3_Opcode = ['00','68','04','18','48','30','0C','2C','4C','3C','38']
    LabelsP2 = ['ADDR','CLEAR','COMPR','SUBR','TIXR']
    P2_Opecode =['90','B4','A0','94','R8']
    LabelsOther =['BYTE','RESW','RESB']
    fr = open(filename)
    numberOfLines = len(fr.readlines())
    INSFromL=[]
    Label = []
    fr = open(filename)
    for line in fr.readlines():
        line = line.strip()
        INSFromL.append(line.split('\t'))
        Label.append(line.split('\t')[1])
        #print (INSFromL)   # instruction from Line
        
    LocCounter = 0
    LocCList = []
    for instr in INSFromL:
       # print (instr)
        if instr[0] == '1' :
            LocCounter = int(instr[3],16)
            LocCList.append(hex(LocCounter))
            LocCList.append(hex(LocCounter))
            
        elif instr[2] in LabelsP3:
            LocCounter +=3
            LocCList.append(hex(LocCounter))
            
        elif instr[2] in LabelsOther:
            if instr[2] == 'BYTE':
                if (instr[3][0]) == 'C':
                    LocCounter += len(instr[3]) - 3
                    LocCList.append(hex(LocCounter))
                elif (instr[3][0]) == 'X':
                    LocCounter += int((len(instr[3]) - 3) / 2)
                    LocCList.append(hex(LocCounter))
                else:
                    print ("error")
                    LocCList.append("error")
                    break;
            if instr[2] == 'RESW':
                LocCounter += int(int(instr[3]) * 3)
                LocCList.append(hex(LocCounter))
            if instr[2] == 'RESB':
                LocCounter += int(instr[3])
                LocCList.append(hex(LocCounter))
        else:
            LocCounter +=2
            LocCList.append(hex(LocCounter))
            
    LocCList = hexi(LocCList)
    print (LocCList[0:numberOfLines])
  #  print(Label[:numberOfLines])

    OpCode = []
    OpCode.append(" ")
    for Stament in INSFromL:
        if Stament[2] in LabelsP3 and Stament[2] != 'END':
            if Stament[2] == 'WORD':
                WORDop =[]
                WORDop.append(hex(int(Stament[3])))
                WORDop = hexi(WORDop)
                #print(''.join(c for c in WORDop))
                OpCode.append(''.join(c for c in WORDop))
            elif Stament[3] in Label:                
                if Stament[3] == ' ':
                    #print ("BUG1")
                    OpCode.append("BUG1")
                else:
                    #print (P3_Opcode[LabelsP3.index(Stament[2])] + LocCList[Label.index(Stament[3])])
                    OpCode.append(P3_Opcode[LabelsP3.index(Stament[2])] + LocCList[Label.index(Stament[3])])
            elif Stament[3].split(',')[1] == 'X':
                temp = LocCList[Label.index(Stament[3].split(',')[0])]
                temp_hex = str(hex(int(temp[0])+8))
                op_string = temp_hex[2:len(temp_hex)] +temp[1:len(temp)]
                #print((P3_Opcode[LabelsP3.index(Stament[2])]) + op_string)
                OpCode.append((P3_Opcode[LabelsP3.index(Stament[2])]) + op_string)
            else:
                #print("BUG2")
                OpCode.append("BUG2")
                
                 
        elif Stament[2] in LabelsOther:
            if Stament[2] == 'BYTE':
                if (Stament[3][0]) == 'C':
                    end = len(Stament[3])
                    toascii = Stament[3][2:end-1]       #del'C'
                    toasciiLen = len(toascii)
                    BYTEop =[]
                    for i in range(toasciiLen):
                        BYTEop.append(hex(int(''.join(str(ord(toascii[i]))))))
                    BYTEop = hexi(BYTEop)
                    #print (''.join(c for c in BYTEop ))
                    OpCode.append(''.join(c for c in BYTEop ))
                elif (Stament[3][0]) == 'X':
                    '''
                    end = len(Stament[3])
                    toascii = Stament[3][2:end-1]       #del'B'
                    toasciiLen = len(toascii)
                    BYTEop =[]
                    for i in range(toasciiLen):
                        BYTEop.append(hex(int(''.join(str(ord(toascii[i]))))))
                    BYTEop = hexi(BYTEop)
                    #print (''.join(c for c in BYTEop ))
                    '''
                    OpCode.append(Stament[3][2:len(Stament[3])-1])
            else:
                OpCode.append(" ")
    OpCode.append(" ")
    OpCode = fit6(OpCode)
    print(OpCode)
    Out_txt(LocCList,INSFromL,OpCode)
                    

  


    


