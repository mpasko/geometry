package view;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.locks.ReentrantLock;

import model.Model;
import formatter.IFormatter;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Watcher implements Runnable, IAlgorithmController {

	private IController control;
	private IFormatter form;
	private Model model;
	private InputStream input;
	private java.util.concurrent.locks.Lock lock;
	private int time = 1000;
	private boolean state = false;
	private BufferedInputStream bis = null;
	private String filename = "";
	private int step_num;

	public Watcher(IController c, IFormatter form, InputStream str) {
		this.control = c;
		this.form = form;
		this.input = str;
		this.lock = new ReentrantLock();
		bis = null;
		this.lock.lock();
		step_num = 0;
	}

	@Override
	public void run() {
		try {
			while (true) {
				int cnt;
				boolean aval;
				lock.lock();
				cnt = time;
				lock.unlock();
				//System.out.println("waiting for entry...");
				//if(false)throw new InterruptedException();
				//do{

				
//				while (!aval) {
//					Thread.sleep(cnt);
//					lock.lock();
//					cnt = time;
//					aval = state;
//					lock.unlock();
//				}
				//}while(bis.available()<=0);
				next();
				Thread.sleep(cnt);

			}
		}catch(Exception e){
			e.printStackTrace();
		}finally {
			//lock.unlock();
		}
	}

	@Override
	public void start() {
		if(!state)
			lock.unlock();
		state = true;
	}

	@Override
	public void stop() {
		if(state)
			lock.lock();
		state = false;
	}

	@Override
	public void setTimeInterval(int miliseconds) {
		lock.lock();
		this.time = miliseconds;
		lock.unlock();
	}

	@Override
	public void setFilename(String filename) {
		this.filename = filename;
		reload();
	}

	@Override
	public void next() {
		++step_num;
		synchronized (control.GetModel()) {
			this.model = form.getNextStep(bis, control.GetModel());
			control.Refresh(model);
			//control.GetModel().notifyAll();
		}
		try {
			if(bis.available()==0){
				reload();
			}
		} catch (IOException ex) {
			//Logger.getLogger(Watcher.class.getName()).log(Level.SEVERE, null, ex);
			reload();
		}
	}

	@Override
	public void reload() {
		step_num = 0;
		if (reloadable()) {
			try {
				if (this.bis != null) {
					bis.close();
				}
				this.bis = new BufferedInputStream(new FileInputStream(filename));
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	@Override
	public boolean reloadable() {
		return !filename.isEmpty();
	}

	@Override
	public void prev() {
		this.reload();
		for(int j = 0; j<step_num; ++j){
			this.next();
		}
		--step_num;
	}
}
