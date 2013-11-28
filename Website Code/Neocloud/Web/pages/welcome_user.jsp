<%@ page contentType="text/html; charset=UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags"%>
<html>
<head>
<link rel="stylesheet" type="text/css" href="pages/results.css">
</head>
<body class="body-class">
	<div id="container" >
		<div class="header">BestPrice App</div>
		<br />

		</div>
 <div id="content" style="height:90%;width:100%;float:left; text-align: center;">
	<h3>
	<br/>
	<br/>
	<br/>
	<br/>
	<br/>
	<br/>
	<br/>
	<br/>
		<font size="7" color="black">Hello</font>
		<font size="7" color="black"><s:property value="username"  /> !!!</font>
	
	 </h3>  
	
	<br/>
	<h2>
				<s:form action="SearchProductList" style="text-align: center;">
					<s:textfield name="searchProduct" theme="css_xhtml" style="text-align: center; font-size:20px; width: 40%"><font size="7" color="black"> Search:</font></s:textfield>
					
					<div class="button" style="text-align: center;">
					    <br/>
						<button type="submit" style="text-align: center; font-size:20px; margin-left: 50px;"><font size="4" color="black">Go Search !!</font></button>
					</div>​
				</s:form>
			</h2>
		</div>
	
	
<div class="footer">Team NeoCloud</div>

</body>
</html>


