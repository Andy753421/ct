<?php
	$jpgs = shell_exec("cd images && ls -1 *.jpg");
	$jpgs = explode("\n", $jpgs);
	foreach ($jpgs as $jpg) {
		#imagecreatefromjpeg($jpg);
		

		### begin resize ###
		list($sw, $sh) = getimagesize("images/$jpg");
		$mw = 200;
		$mh = 200;
		if ($sw > $mw || $sh > $mh) {
			if ($sw > $sh) {
				$dw = $mw;
				$dh = $sh*($mw/$sw);
			}
			if ($sh > $sw) {
				$dh = $mh;
				$dw = $sw*($mh/$sh);
			}
		} else {
			$dw = $sw;
			$dh = $sh;
		}
		$src_image = imagecreatefromjpeg("images/$jpg");
		$dst_image = imagecreatetruecolor($dw, $dh);
		imagecopyresampled($dst_image, $src_image, 0, 0, 0, 0, $dw, $dh, $sw, $sh);
		imagejpeg($dst_image, "thumbs/{$jpg}");
		### end resize ###

		print("<br>".$jpg);
	}
?>
