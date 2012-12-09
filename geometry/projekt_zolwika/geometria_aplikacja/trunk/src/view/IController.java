package view;
import java.awt.Color;

import model.Model;

import formatter.IFormatter;


public interface IController {
	void CloseEditedShape();
	void SetColor(Color c);
	void Save(String filename);
	void Load(String filename);
        void Reload();
	void SetFormatter(IFormatter formatter);
	void ResetView();
	void AddPoint();
	void SetZoom(int value);
	void Refresh(Model m);
	Model GetModel();
}
