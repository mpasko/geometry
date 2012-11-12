package formatter;
import java.io.InputStream;
import java.io.PrintStream;

import model.Model;


public interface IFormatter {
	Model loadAll(InputStream in);
	void saveAll(PrintStream out, Model model);
	Model getNextStep(InputStream in, Model current);
}
