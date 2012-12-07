package view;

public interface IAlgorithmController {

	void start();

	void stop();

	void setTimeInterval(int miliseconds);

	void setFilename(String filename);

	void next();
	
	void reload();
	
	boolean reloadable();
	
	void prev();
}
