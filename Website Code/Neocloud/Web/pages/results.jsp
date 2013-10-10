<%@ page contentType="text/html; charset=UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags"%>
<html>
<head>
<link rel="stylesheet" type="text/css" href="pages/results.css">
</head>
<body>
<body>
	<div id="container" style="width: 100%">

		<div id="header" style="background-color: #606060; width:100%; height:20%; text-align: center; padding-top: 5px;">

			<h1 style="font-size:60px;text-align: center;">Smart Price App</h1>
		</div>
 
 <div id="content" style="padding-top:156px; background-color:#EEEEEE;height:80%;width:100%;float:left;text-align: center;text-align: center;">

<h2>
	Results are : <s:property value="%{searchProductList}"/>
	<br/>
	Lowest Price is : <s:property value="%{productPrice}"/>
	</h2>
<div class="product-info"><p class="meta-text">Ebay<br></p>
</div>
<div class="product-info"><p class="meta-text">Amazon<br></p>
</div>
<div class="product-info"><p class="meta-text">Walmart<br></p>
</div>
<div class="product-info"><p class="meta-text">Best Buy<br></p>
</div>
</div>
	
 <div id="footer"
			style="background-color: #606060  ; clear: both; text-align: center;">
			Team NeoCloud</div>
	</div>
</body>
</html>


