<html>
<head>
<style>
	.gallery_item_con {
		text-decoration:none;
		/*padding-top:5px;
		padding-top:5px;*/
		margin:10px;
		display:block;
		height:210px;
		width:210px;
		text-align:center;
		float:left;
	}
		
	.gallery_item {
		text-decoration:none;
		background-color:#f8fbFF;
		border:solid 1px #B4C7F8;
		/*padding-top:5px;
		padding-top:5px;*/
		padding:5px;
		display:block;
		/*height:210px;*/
		text-align:center;
	}
	.gallery_item img {
		border:none;
	}
	.gallery_item:hover {
		color:#0D378D;
	}
</style>
</head>
<body>
<center>
	<a href="frames.php">Frames</a>
</center>
<?php
$thumbs = shell_exec("cd thumbs && ls -1 *.jpg");
$thumbs = explode("\n", $thumbs);
array_pop($thumbs);
foreach ($thumbs as $thumb) {
	print("<div class=\"gallery_item_con\">\n");
	print("\t<a class=\"gallery_item\" href=\"images/$thumb\">\n");
	print("\t\t<img src=\"thumbs/$thumb\">\n");
	print("\t</a>\n");
	print("</div>\n");
}
?>
</body>
</html>
