<html>
<head>
<style>
	.gallery_item_con {
		text-decoration:none;
		/*padding-top:5px;
		padding-top:5px;*/
		margin-top:5px;
		margin-bottom:5px;
		display:block;
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

<?php
$thumbs = shell_exec("cd thumbs && ls -1 *.jpg");
$thumbs = explode("\n", $thumbs);
array_pop($thumbs);
foreach ($thumbs as $thumb) {
	print("<div class=\"gallery_item_con\">\n");
	print("\t<a class=\"gallery_item\" href=\"images/$thumb\" target=\"content\">\n");
	print("\t\t<img src=\"thumbs/$thumb\">\n");
	print("\t</a>\n");
	print("</div>\n");
}
?>
</body>
</html>
