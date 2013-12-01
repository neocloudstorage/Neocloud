<%@page import="com.opensymphony.xwork2.inject.Context"%>
<%@page import="java.util.ArrayList"%>
<%@ page contentType="text/html; charset=UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags"%>
<html>
<head>
<link rel="stylesheet" type="text/css" href="pages/results.css">
</head>
<body>
<body class="body-class">
	<div id="container" >

		<div class="header">
			BestPrice App
		</div>
 
 <div id="content" style="padding-top:156px;height:80%;width:100%;float:left;text-align: center;text-align: center;">

<h2>
	Results are : <s:property value="%{searchProductList}"/>
	<br/>
	Lowest Price is : <s:property value="%{productPrice}"/>
</h2>

<div class="product-info">
	<img class="imgClass" src="http://2.bp.blogspot.com/-iyrT2e_ONm0/ThRvL224gbI/AAAAAAAASOo/7ojEVUaUnx0/s200/Ebay_Logo.jpg"/>
	<s:iterator value="ebayResults">
	  <p class="meta-text"><br>
	  <s:property value="name"/><br>
		Price: $<s:property value="price"/><br>
		<a href=<s:property value="url"/>>Visit Link</a><br>
	</p>
	   </s:iterator>
		
</div>
<div class="product-info">
	<img class="imgClass" src="http://ts2.mm.bing.net/th?id=H.4986879105631917&w=186&h=109&c=7&rs=1&pid=1.7"/>
	<s:iterator value="amazonResults">
	  <p class="meta-text"><br>
	  <s:property value="name"/><br>
		Price: <s:property value="price"/><br>
		<a href=<s:property value="url"/>>Visit Link</a><br>
	</p>
	   </s:iterator>
</div>
<div class="product-info">
	<img class="imgClass" src="http://ts3.mm.bing.net/th?id=H.5029227475634718&w=275&h=188&c=7&rs=1&pid=1.7"/>
	<p class="meta-text">Walmart<br></p>
</div>
<div class="product-info">
	<img class="imgClass" src="http://ts2.mm.bing.net/th?id=H.4952841474999769&w=220&h=161&c=7&rs=1&pid=1.7"/>
	<p class="meta-text">Best Buy<br></p>
</div>
</div>

 <div id="footer" class="footer">
			Team NeoCloud</div>
	</div>
</body>
</html>


