// Saves screenshot as PNG file.
using UnityEngine;
using System.Collections;
using System.IO;

public class getPic : MonoBehaviour {
	// Take a shot immediately
	IEnumerator Start () {
		yield return UploadPNG();
	}

	IEnumerator UploadPNG() {
		// We should only read the screen buffer after rendering is complete
		yield return new WaitForEndOfFrame ();

		// Create a texture the size of the screen, RGB24 format
		int width = Screen.width;
		int height = Screen.height;
		Texture2D tex = new Texture2D (width, height, TextureFormat.RGB24, false);

		// Read screen contents into the texture
		tex.ReadPixels (new Rect (0, 0, width, height), 0, 0);
		tex.Apply ();

		// Encode texture into PNG
		byte[] bytes = tex.EncodeToPNG ();
		Object.Destroy (tex);

		// 
		File.WriteAllBytes ("/Users/kenjif/Documents/cours/projetCV/3D_Vision/unity/pics/test.png", bytes);
	}
}