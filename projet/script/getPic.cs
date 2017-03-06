// Saves screenshot as PNG file.
using UnityEngine;
using System.Collections;
using System.IO;

public class getPic : MonoBehaviour {

	void Start () {

	}

	void move (string tag, char c, float dist) {
		Vector3 position = GameObject.FindGameObjectWithTag (tag).transform.position;
		if (c.Equals('x')) position.x = position.x + dist;
		if (c.Equals('y')) position.y = position.y + dist;
		if (c.Equals('z')) position.z = position.z + dist;
		GameObject.FindGameObjectWithTag (tag).transform.position = position;
	}

	void reset (string tag, Vector3 initial) {
		GameObject.FindGameObjectWithTag (tag).transform.position = initial;
	}

	private IEnumerator SS() {
		Vector3 tmp = GameObject.FindGameObjectWithTag ("bob").transform.position;
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 5; i++) {
				// Wait untill we actually rendered
				yield return new WaitForEndOfFrame ();

				Texture2D texture = new Texture2D (Screen.width, Screen.height, TextureFormat.RGB24, false);

				// Read screen contents into the texture
				texture.ReadPixels (new Rect (0, 0, Screen.width, Screen.height), 0, 0);
				texture.Apply ();

				// Write to file
				byte[] bytes = texture.EncodeToPNG ();
				System.IO.File.WriteAllBytes ("/Users/kenjif/Documents/cours/projetCV/3D_Vision/projet/projet.app/Contents/MacOS/source/cam" + j + "-dist" + i + ".png", bytes);

				// Clean up the used texture
				Destroy (texture);

				// move bob
				move ("bob", 'z', 1);
			}
			// reset bob to initial position and move each camera
			reset ("bob", tmp);
			move ("camera_left" , 'x', -0.05f);
			move ("camera_right", 'x',  0.05f);
		}
	}

	void Update ()
	{
		if (Input.GetKeyDown (KeyCode.K)) {
			StartCoroutine (SS ());
		}
	}
}
