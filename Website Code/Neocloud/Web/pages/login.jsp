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
			<s:form action="Welcome" theme="simple" style="text-align: center; font-size:25px; font-color:Red"> 
			<br/>
			<br/>
				<font size="7" color="black">Username </font>:<s:textfield name="username" class="input" />
				<br>
				<font size="7" color="black">Password </font>:<s:password name="password" class="input" />
				<br>
				<s:submit value="Login" style="text-align: center; font-size:25px;" />
			</s:form>
			<h2>
				<s:form action="SearchProductList" style="text-align: center;">
					<s:textfield name="searchProduct" theme="css_xhtml" style="text-align: center; font-size:20px; width: 40%"><font size="7"> Search:</font></s:textfield>
					<div class="button" style="text-align: center;">
						<button type="submit" style="text-align: center; font-size:20px; margin-left: 50px;">Go Search !!</button>
					</div>​
				</s:form>
			</h2>
		</div>
		<div class="footer">Team NeoCloud</div>
	</div>
</body>
</html>


