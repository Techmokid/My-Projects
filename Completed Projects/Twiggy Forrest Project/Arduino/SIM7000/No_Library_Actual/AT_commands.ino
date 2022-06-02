/*
 * 
 * ATE0
 * OK
 * 
 * AT+CFUN=0
 * OK
 * 
 * AT+CFUN=1,1
 * OK
 * 
 * AT
 * AT
 * AT
 * AT
 * AT
 * OK
 * 
 * ATE0
 * OK
 * 
 * AT+CMEE=2
 * OK
 * 
 * AT+GMM
 * SIMCOM_SIM7000G
 * OK
 * 
 * AT+CLTS=1
 * OK
 * 
 * AT+CBATCHK=1
 * OK
 * 
 * AT+CPIN?
 * +CPIN: READY
 * 
 * AT+GMM
 * SIMCOM_SIM7000G
 * 
 * ATI
 * SIM7000G R1529
 * 
 * -------------------------------------------------------------------------- 
 * 
 * AT+CEREG?
 * +CEREG: 0,1
 * OK
 * 
 * AT+CIPSHUT
 * SHUT OK
 * 
 * AT+CGATT=0
 * OK
 * 
 * AT+SAPBR=3,1,"Contype","GPRS"
 * OK
 * 
 * AT+SAPBR=3,1,"APN","telstra.wap"
 * OK
 * 
 * AT+CGDCONT=1,"IP","telstra.wap"
 * OK
 * 
 * AT+CGATT=1
 * OK
 * 
 * AT+CGACT=1,1
 * OK
 * 
 * AT+SAPBR=1,1
 * OK
 * 
 * AT+SAPBR=2,1
 * +SAPBR: 1,1,"10.216.175.18"
 * OK
 * 
 * AT+CIPMUX=1
 * OK
 * 
 * AT+CIPQSEND=1
 * OK
 * 
 * AT+CIPRXGET=1
 * OK
 * 
 * AT+CSTT="telstra.wap","",""
 * OK
 * 
 * AT+CIICR
 * OK
 * 
 * AT+CIFSR;E0
 * 10.216.175.18
 * OK
 * 
 * AT+CGATT?
 * +CGATT: 1
 * OK
 * 
 * AT+CIFSR;E0
 * 10.216.175.18
 * OK
 * 
 * AT+CIPCLOSE=0
 * +CME ERROR: operation not allowed
 * 
 * AT+CIPSTART=0,"TCP","techmo.unity.chickenkiller.com",80
 * OK
 * 0, CONNECT OK
 * 
 * AT+CIPSEND=0,16
 * >GET / HTTP/1.1
 * DATA ACCEPT:0,16
 * 
 * AT+CIPSEND=0,38
 * >Host: techmo.unity.chickenkiller.com
 * DATA ACCEPT:0,38
 * 
 * AT+CIPSEND=0,15
 * >Getinfoonid:6
 * AT+CIPSEND=0,15
 * 
 * AT+CIPSEND=0,13
 * >Accept: * /*              <-- No space between the asterixes
 * DATA ACCEPT:0,13
 *
 * AT+CIPSEND=0,21
 * >Connection: close
 * DATA ACCEPT:0,21
 * 
 * AT+CIPSEND=0,2
 * >                          <-- Put the ctrl-Z special character here
 * DATA ACCEPT:0,2
 * 
 * AT+CIPRXGET=4,0
 * +CIPRXGET: 4,0,0
 * OK
 * 
 * AT+CIPSTATUS=0
 * +CIPSTATUS: 0,0,"TCP","169.47.130.74","80","CONNECTED"
 * OK
 * 
 * AT+CIPRXGET=4,0
 * +CIPRXGET: 4,0,0
 * OK
 * 
 * AT+CIPSTATUS=0
 * +CIPSTATUS: 0,0,"TCP","169.47.130.74","80","CONNECTED"
 * OK
 * 
 * AT+CIPRXGET=4,0
 * +CIPRXGET: 4,0,0
 * OK
 * 
 * AT+CIPSTATUS=0
 * +CIPSTATUS: 0,0,"TCP","169.47.130.74","80","CONNECTED"
 * OK
 * 
 * +CIPRXGET: 1,0
 * 
 * AT+CIPRXGET=4,0
 * +CIPRXGET: 4,0,341
 * OK
 * 
 * AT+CIPRXGET=4,0
 * +CIPRXGET: 4,0,341
 * OK
 * 
 * AT+CIPRXGET=2,0,341
 * +CIPRXGET: 2,0,341,0
 * 
 * --HERE IS WHERE THE OUTPUT OF THE SERVER WOULD BE--
 * 
 * OK
 * 
 * 0,CLOSED
 * 
 * AT+CIPRXGET=4,0
 * +CIPRXGET: 4,0,0
 * OK
 * 
 * AT+CIPSTATUS=0
 * +CIPSTATUS: 0,0,"TCP","169.47.130.74","80","CLOSED"
 * OK
 * 
 * AT+CIPCLOSE=0
 * +CME ERROR: operation not allowed
 */
