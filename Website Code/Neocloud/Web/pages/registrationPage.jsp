<%@ page contentType="text/html; charset=UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags"%>
<html>
<head>
<link rel="stylesheet" type="text/css" href="pages/results.css">
</head>
<body class="body-class">


	<div class="container" style="width: 100%">

		<div class="header">BestPriceApp</div>
		<div class="content">
			<br />
			<s:form action="RegisterInDB" theme="simple" style="text-align: center; font-size:25px; font-color:Red"> 
			<br/>
			<br/>
			<br/>
			
			    <font size="6" color="black">&nbsp&nbsp&nbsp&nbsp Email </font>: <s:textfield name="email"  class="input" />
				<br>
				<br/>
				<font size="6" color="black">Username </font>: <s:textfield name="username"  class="input" />
				<br>
				<br/>
				<font size="6" color="black">Password </font>: <s:password name="password"  class="input" />
				<br>
				<br/>
				<s:submit value="Register Me !!" style="text-align: center; font-size:25px;" />
			</s:form>
		</div>
		<div class="footer">Team NeoCloud</div>
	</div>
</body>
</html>


